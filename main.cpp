/*
Name: Vrishank Kulkarni 
ID: 3115417
Class: EECS 348 lab 07
Lab time: Wednesday 1-2:50

Objectives:
AddMatrices: This function should take two matrices as input and return their sum using operator overloading.
MultiplyMatrices: This function should take two matrices as input and return their
roduct using operator overloading.
Diagonal sum: take the diagnols of a matrix and add them
Display: print the matrix in a user-friendly format
Swap Rows: swap the rows of a matrix
Error checking: check if the dimensions are valid for addition and multiplication, and if the indicies are valid for row swapping.
 */


#include <iostream>
#include <fstream>
using namespace std;

const int SIZE = 4; 

class Matrix {
private:
    int data[SIZE][SIZE]; 

public:
    // 1. Read values from a file into the matrix, with optional row reversal
    bool readFromFile(const string& filename, bool reverseRows = false) {
        ifstream file(filename); 
        if (!file.is_open()) {   
            cout << "Error: Could not open file." << endl;
            return false;   //return false if file can't be opened
        }

        for (int i = 0; i < SIZE; ++i) {
            int row = reverseRows ? SIZE - i - 1 : i; 
            for (int j = 0; j < SIZE; ++j) {
                file >> data[row][j]; //read each element from the file into the appropriate row
            }
        }
        file.close(); 
        return true;  
    }

    // 2. Display the matrix in a readable format
    void display() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                cout << data[i][j] << " "; //print space in between each number
            }
            cout << endl; //add new line after every row
        }
    }

    // 3. Overload the + operator to add two matrices
    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                //add elements of the two matrices
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result; 
    }

    // 4. Overload the * operator to multiply two matrices
    Matrix operator*(const Matrix& other) const {
        Matrix result; 
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result.data[i][j] = 0; //initialize the element to 0
                for (int k = 0; k < SIZE; ++k) {
                    //multiply product for matrix multiplication
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        return result; 
    }

    // 5. Compute the sum of the main and secondary diagonal elements
    int sumOfDiagonals() const {
        int mainDiagonalSum = 0;
        int secondaryDiagonalSum = 0;

        //sum elements of the main and secondary diagonals
        for (int i = 0; i < SIZE; ++i) {
            mainDiagonalSum += data[i][i];
            secondaryDiagonalSum += data[i][SIZE - i - 1]; 
        }
        return mainDiagonalSum + secondaryDiagonalSum; 
    }

    // 6. Swap two rows in the matrix, given their indices
    void swapRows(int row1, int row2) {
        if (row1 >= 0 && row1 < SIZE && row2 >= 0 && row2 < SIZE) { //check valid indices
            for (int j = 0; j < SIZE; ++j) {
                //swap each element in the specified rows
                swap(data[row1][j], data[row2][j]);
            }
        }
    }
};

int main() {
    Matrix mat1, mat2;

  
    if (!mat1.readFromFile("matrix-data.txt")) {
        return 1; 
    }
    cout << "Matrix 1:" << endl;
    mat1.display(); 

    cout << "Matrix 2:" << endl;
    mat2.display(); 

   //call class methods
    Matrix sum = mat1 + mat2; 
    cout << "Sum of matrices:" << endl;
    sum.display(); 

    
    Matrix product = mat1 * mat2; 
    cout << "Product of matrices:" << endl;
    product.display(); 

    
    cout << "Sum of diagonals of Matrix 1: " << mat1.sumOfDiagonals() << endl;

    mat1.swapRows(0, 2);
    cout << "Matrix 1 after swapping rows:" << endl;
    mat1.display();

    return 0;
}
