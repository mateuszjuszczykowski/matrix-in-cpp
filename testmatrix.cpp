#include <iostream>
#include "Matrix.h"

using namespace std;

void AssigningCopying();
void Operations();
void LoadingMatricesFromTextFile();
void Errors();

int main(){
	AssigningCopying();
	Operations();
	LoadingMatricesFromTextFile();
	Errors();
	//Matrix(-1, 2);
	/*Matrix MatrixA(2, 2);
	Matrix MatrixC(2, 2);
	MatrixC = MatrixA;
	MatrixA(1, 1) = 2;
	Matrix MatrixB = MatrixA;
	cout << MatrixA << endl;
	cout << MatrixC << endl;
	cout << (MatrixC == MatrixA) << endl;
	cout << (MatrixB != MatrixC) << endl;
	cout << MatrixA * MatrixC << endl;
	cout << MatrixA << endl;
	MatrixA.loadMatrix("matrix.txt");
	cout << MatrixA << endl;
	*/
}

void AssigningCopying(){
	cout << "Testing assigning and copying matrices: " << endl;
	Matrix MatrixA(2, 2);
	MatrixA(0, 0) = 1;
	Matrix MatrixB(MatrixA);
	Matrix MatrixC(2, 2);
	MatrixC = MatrixA;
	cout << "Printing MatrixA: " << endl << MatrixA << endl;
	cout << "Printing MatrixB: " << endl << MatrixB << endl;
	cout << "Printing MatrixC: " << endl << MatrixC << endl;
	cout << "End of testing assigning and copying matrices\n\n\n";
}

void Operations(){
	cout << "Testing operations on matrices: " << endl;
	Matrix MatrixA(3, 3);
	MatrixA(0, 0) = 1;
	MatrixA(0, 1) = 2;
	MatrixA(0, 2) = 3;
	MatrixA(1, 0) = 1;
	MatrixA(1, 1) = 2;
	MatrixA(1, 2) = 3;
	MatrixA(2, 0) = 1;
	MatrixA(2, 1) = 2;
	MatrixA(2, 2) = 3;
	Matrix MatrixB = MatrixA;
	Matrix MatrixC = MatrixA;
	cout << "Reading: (MatrixC(3, 3)) " << MatrixC(2, 2) << endl;
	MatrixC(2, 2) = 4;
	cout << "Writing: (MatrixC(3, 3) = 4) " << MatrixC(2, 2) << endl;
	cout << "Printing MatrixA: " << endl << MatrixA << endl;
	cout << "Printing MatrixB: " << endl << MatrixB << endl;
	cout << "MatrixA + MatrixB: " << endl << (MatrixA + MatrixB) << endl;
	cout << "MatrixA - MatrixB: " << endl << (MatrixA - MatrixB) << endl;
	cout << "MatrixA * MatrixB: " << endl << (MatrixA * MatrixB) << endl;
	cout << "MatrixA += MatrixB: " << endl << (MatrixA += MatrixB) << endl;
	cout << "MatrixA -= MatrixB: " << endl << (MatrixA -= MatrixB) << endl;
	Matrix MatrixD = MatrixA;
	cout << "MatrixA *= MatrixB: " << endl << (MatrixA *= MatrixB) << endl;
	cout << "Printing MatrixD: " << endl << MatrixD << endl;
	cout << "MatrixB == MatrixD(1)" << (MatrixB == MatrixD) << endl;
	cout << "MatrixB == MatrixA(0)" << (MatrixB == MatrixA) << endl;
	cout << "MatrixB != MatrixA(1)" << (MatrixB != MatrixA) << endl;
	cout << "MatrixB != MatrixD(0)" << (MatrixB != MatrixD) << endl;
	cout << "End of testing operations on matrices\n\n\n";
}

void LoadingMatricesFromTextFile(){
	Matrix MatrixA(2, 2);
	cout << "MatrixA before text file: " << endl << MatrixA << endl;
	MatrixA.readFile("matrix.txt");
	cout << "Loaded matrix: " << endl << MatrixA << endl;
}

void Errors(){
	//Matrix MatrixC(-1, 2);
	//Matrix MatrixD(2, -1);
	Matrix MatrixA(2, 2);
	Matrix MatrixB(2, 3);
	//MatrixA + MatrixB;
}