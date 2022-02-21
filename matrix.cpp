#include <iostream>
#include <fstream>
#include "matrix.h"
#include "exceptions.h"

using namespace std;

Matrix::Matrix(int rows, int collumns) {
	if (rows <= 0) {
		throw InvalidRowsSize();
	}
	if (collumns <= 0) {
		throw InvalidColumnsSize();
	}
	double *matrix = new double[rows*collumns];
    //clearing matrix
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < collumns; j++){
			matrix[i * collumns + j] = 0;
		}
	}
	data = new RcMatrix(rows, collumns, matrix);
	delete[] matrix; 
}

Matrix::Matrix(const Matrix &matrix){
	matrix.data->n++;
	data = matrix.data;
}

Matrix::~Matrix(){
	if(--data->n == 0){
		delete data;
	}
}

Matrix Matrix::operator+(const Matrix& matrix) const{
	if(data->m_rowsSize != matrix.data->m_rowsSize || data->m_colsSize != matrix.data->m_colsSize){
		throw WrongMatricesSizes();
	}
	Matrix temp(data->m_rowsSize, data->m_colsSize);
	for(int i = 0; i < data->m_rowsSize; i++){
		for(int j = 0; j < data->m_colsSize; j++){
			temp.data->m_matrix[i * data->m_colsSize + j] = data->m_matrix[i * data->m_colsSize + j] + matrix.data->m_matrix[i * data->m_colsSize + j];
		}
	}
	return temp;
}

Matrix Matrix::operator-(const Matrix& matrix) const{
	if(data->m_rowsSize != matrix.data->m_rowsSize || data->m_colsSize != matrix.data->m_colsSize){
		throw WrongMatricesSizes();
	}
	Matrix temp(data->m_rowsSize, data->m_colsSize);
	for(int i = 0; i < data->m_rowsSize; i++){
		for(int j = 0; j < data->m_colsSize; j++){
			temp.data->m_matrix[i * data->m_colsSize + j] = data->m_matrix[i * data->m_colsSize + j] - matrix.data->m_matrix[i * data->m_colsSize + j];
		}
	}
	return temp;
}

Matrix Matrix::operator*(const Matrix& matrix) const{
	if(data-> m_colsSize != matrix.data->m_rowsSize){
		throw WrongMatricesSizes();
	}
	Matrix temp(data->m_rowsSize, matrix.data->m_colsSize);
	for(int i = 0; i < data->m_rowsSize; i++){
		for(int j = 0; j < matrix.data->m_colsSize; j++){
			for(int k = 0; k < matrix.data->m_rowsSize; k++){
				temp.data->m_matrix[i*temp.data->m_colsSize + j] += 
				data->m_matrix[i*data->m_rowsSize + k] * matrix.data->m_matrix[k*matrix.data->m_rowsSize + j];
			}
		}
	}
	return temp;
}

Matrix& Matrix::operator+=(const Matrix& matrix){
	if(data->m_rowsSize != matrix.data->m_rowsSize || data->m_colsSize != matrix.data->m_colsSize){
		throw WrongMatricesSizes();
	}
	data = data->detach();
	for(int i = 0; i < data->m_rowsSize; i++){
		//cout << "test1" << endl;
		for(int j = 0; j < data->m_colsSize; j++){
			//cout << "test2" << endl;
			data->m_matrix[i * data->m_colsSize + j] += matrix.data->m_matrix[i * data->m_colsSize + j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix){
	if(data->m_rowsSize != matrix.data->m_rowsSize || data->m_colsSize != matrix.data->m_colsSize){
		throw WrongMatricesSizes();
	}
	data = data->detach();
	for(int i = 0; i < data->m_rowsSize; i++){
		for(int j = 0; j < data->m_colsSize; j++){
			data->m_matrix[i * data->m_colsSize + j] -= matrix.data->m_matrix[i * data->m_colsSize + j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& matrix){
	if(data-> m_colsSize != matrix.data->m_rowsSize){
		throw WrongMatricesSizes();
	}
	Matrix temp(data->m_rowsSize, matrix.data->m_colsSize);
	for(int i = 0; i < data->m_rowsSize; i++){
		for(int j = 0; j < matrix.data->m_colsSize; j++){
			for(int k = 0; k < matrix.data->m_rowsSize; k++){
				temp.data->m_matrix[i*temp.data->m_colsSize + j] += 
				data->m_matrix[i*data->m_rowsSize + k] * matrix.data->m_matrix[k*matrix.data->m_rowsSize + j];
			}
		}
	}
	data = data->detach();
	*this = temp;
	return *this;
}

Matrix& Matrix::operator=(const Matrix& matrix){
	matrix.data->n++;
	if(--data->n == 0){
		delete data;
	}
	data = matrix.data;
	return *this;
}

bool Matrix::operator==(const Matrix& matrix) const{
	if(data->m_rowsSize != matrix.data->m_rowsSize || data->m_colsSize != matrix.data->m_colsSize){
		return false;
	}
	for(int i = 0; i < data->m_rowsSize; i++){
		for(int j = 0; j < data->m_colsSize; j++){
			if(data->m_matrix[i * data->m_colsSize + j] != matrix.data->m_matrix[i * data->m_colsSize + j]){
				return false;
			}
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& matrix) const{
	return !(*this == matrix);
}

double Matrix::operator()(int row, int col) const{
	check(row, col);
	return data->m_matrix[row*data->m_colsSize + col];
}

Matrix::Mref Matrix::operator()(int row, int col){
	check(row, col);
	return Mref(data->m_matrix[row*data->m_colsSize + col], *this);
}

void Matrix::check(int row, int col) const{
	if(row >= data->m_rowsSize || row < 0){
		throw InvalidRowsSize();
	}
	if(col >= data->m_colsSize || col < 0){
		throw InvalidColumnsSize();
	}
}

void getMatrixSizes(ifstream &file, int &rowSize, int &colSize){
	string line;
	bool colsNotCounted = true;
	while(getline(file, line)){
		int i = 0;
		if(colsNotCounted){
			while(line[i] != '\0'){
				colsNotCounted = false;
				if(isspace(line[i])){
					colSize++;
				}
				i++;
			}
			colSize++;
		}
		rowSize++;
	}
}

void getMatrixData(ifstream &file, double *fmatrix, int colSize){
	int rows = 0;
	int cols = 0;
	int i;
	string number;
	string line;
	while(getline(file, line)){
		i = 0;
		cols = 0;
		number.clear();
		while(1){
			if(isspace(line[i]) || line[i] == '\0'){
				fmatrix[rows*colSize + cols] = stod(number);
				cols++;
				number.clear();
				if(line[i] == '\0'){
					break;
				}
			}
			else{
				number.push_back(line[i]);
			}
			i++;
		}
		rows++;
	}	
}

void Matrix::readFile(const string &filename){
	ifstream file (filename);
	int rowSize = 0;
	int colSize = 0;
	if(file.is_open()){
		getMatrixSizes(file, rowSize, colSize);
		if(rowSize != data->m_rowsSize || colSize != data->m_colsSize){
			throw WrongMatricesSizes();
		}
		file.clear();
		file.seekg(0);
		double *fmatrix = new double[rowSize * colSize];
		getMatrixData(file, fmatrix, colSize);
		file.close();
		data = data->detach();
		data->m_rowsSize = rowSize;
		data->m_colsSize = colSize;
		for(int i = 0; i < data->m_rowsSize; i++){
			for(int j = 0; j < data->m_colsSize; j++){
				data->m_matrix[i*data->m_colsSize + j] = fmatrix[i*data->m_colsSize + j];
			}
		}
		delete [] fmatrix;
	}
	else{
		cout << "Unable to open the file." << endl;
	}
}

ostream& operator<<(ostream& o, const Matrix& matrix){
	for(int i = 0; i < matrix.data->m_rowsSize; i++){
		o << "{";
		for(int j = 0; j < matrix.data->m_colsSize; j++){
			o << " " << matrix.data->m_matrix[i*matrix.data->m_colsSize + j] << " ";
		}
		o << "}" << endl;
	}
	return o;
}

Matrix::RcMatrix::RcMatrix(int rows, int cols, const double *matrix)
	: m_matrix(new double[rows*cols]), n(1), m_rowsSize(rows), m_colsSize(cols)
{
	for(int i = 0; i < m_rowsSize; i++){
		for(int j = 0; j < m_colsSize; j++){
			m_matrix[i*m_colsSize + j] = matrix[i*m_colsSize + j];
		}
	}
}

Matrix::RcMatrix* Matrix::RcMatrix::detach(){
	if (n == 1){
		return this;
	}
	RcMatrix *t = new RcMatrix(m_rowsSize, m_colsSize, m_matrix);
	n--;
	return t;
}

Matrix::RcMatrix::~RcMatrix(){
	delete[] m_matrix;
}
