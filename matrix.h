#include <iostream>
#pragma once

using namespace std;

class Matrix {
	private:
		struct RcMatrix;
		RcMatrix *data;
	public:
		class Mref;
		Mref operator()(int row, int collumn);

		Matrix(int rows, int collumns);
		Matrix(const Matrix &matrix);
		~Matrix();

		Matrix operator+(const Matrix& matrix) const;
		Matrix operator-(const Matrix& matrix) const;
		Matrix operator*(const Matrix& matrix) const;
		Matrix& operator+=(const Matrix& matrix);
		Matrix& operator-=(const Matrix& matrix);
		Matrix& operator*=(const Matrix& matrix);
		Matrix& operator=(const Matrix& matrix);
		bool operator==(const Matrix& matrix) const;
		bool operator!=(const Matrix& matrix) const;
		double operator()(int row, int col) const;

		friend ostream& operator<<(ostream& o, const Matrix& matrix);
		void check(int row, int collumn) const;
		void readFile(const string &filename);

};

struct Matrix::RcMatrix{
	double *m_matrix;
	int n;
	int m_rowsSize;
	int m_colsSize;
	RcMatrix(int rows, int cols);
	RcMatrix* detach();
	~RcMatrix();
	friend class Matrix;
	friend class Mref;
	private:
		RcMatrix(int rows, int cols, const double *matrix);
		RcMatrix& operator=(const RcMatrix& matrix);
};

class Matrix::Mref {
  private:
	double& m_value;
	Matrix& m_matrix;
  public:
	Mref(double& value, Matrix &matrix) : m_value(value), m_matrix(matrix) {}
	void operator=(double value) {
		m_value = value;
	}
	operator double() const {
		m_matrix.data = m_matrix.data->detach();
		return m_value;
	}
};