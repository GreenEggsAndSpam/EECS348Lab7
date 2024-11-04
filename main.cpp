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
#include <vector>
using namespace std;

const int SIZE = 4; // Define a constant for the matrix size (4x4 matrix)

class Matrix {
private:
    int data[SIZE][SIZE]; // 2D array to store matrix data

public:
    // 1. Read values from a file into the matrix, with optional row reversal
    bool readFromFile(const string& filename, bool reverseRows = false) {
        ifstream file(filename); // Open the file
        if (!file.is_open()) {   // Check if file opened successfully
            cout << "Error: Could not open file." << endl;
            return false;        // Return false if file can't be opened
        }

        // Temporary storage to read the matrix and reverse if needed
        vector<vector<int> > tempData(SIZE, vector<int>(SIZE));


        // Read values from the file into the temporary matrix
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                file >> tempData[i][j];
            }
        }
        file.close(); // Close the file after reading

        // Copy the data, optionally reversing the rows
        for (int i = 0; i < SIZE; ++i) {
            int row = reverseRows ? SIZE - i - 1 : i; // Calculate the row index based on reverse flag
            for (int j = 0; j < SIZE; ++j) {
                data[i][j] = tempData[row][j];
            }
        }
        return true;  // Return true to indicate successful reading
    }

    // 2. Display the matrix in a readable format
    void display() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                cout << data[i][j] << " "; // Print each element with a space
            }
            cout << endl; // New line after each row
        }
    }

    // 3. Overload the + operator to add two matrices
    Matrix operator+(const Matrix& other) const {
        Matrix result; // Create a new matrix to store the result
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                // Add corresponding elements of the two matrices
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result; // Return the resulting matrix
    }

    // 4. Overload the * operator to multiply two matrices
    Matrix operator*(const Matrix& other) const {
        Matrix result; // Create a new matrix to store the product
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result.data[i][j] = 0; // Initialize the element to 0
                for (int k = 0; k < SIZE; ++k) {
                    // Multiply and accumulate the product for matrix multiplication
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        return result; // Return the resulting product matrix
    }

    // 5. Compute the sum of the main and secondary diagonal elements
    int sumOfDiagonals() const {
        int mainDiagonalSum = 0;
        int secondaryDiagonalSum = 0;

        // Sum elements of the main and secondary diagonals
        for (int i = 0; i < SIZE; ++i) {
            mainDiagonalSum += data[i][i]; // Main diagonal element
            secondaryDiagonalSum += data[i][SIZE - i - 1]; // Secondary diagonal element
        }
        return mainDiagonalSum + secondaryDiagonalSum; // Return the total diagonal sum
    }

    // 6. Swap two rows in the matrix, given their indices
    void swapRows(int row1, int row2) {
        if (row1 >= 0 && row1 < SIZE && row2 >= 0 && row2 < SIZE) { // Check valid indices
            for (int j = 0; j < SIZE; ++j) {
                // Swap each element in the specified rows
                swap(data[row1][j], data[row2][j]);
            }
        }
    }
};

int main() {
    Matrix mat1, mat2;

    // Load matrix data from file for Matrix 1 without row reversal
    if (!mat1.readFromFile("matrix-data.txt")) { // Load Matrix 1
        return 1; // Exit if file cannot be opened
    }
    cout << "Matrix 1:" << endl;
    mat1.display(); // Display Matrix 1

    // Load matrix data from file for Matrix 2 with row reversal
    if (!mat2.readFromFile("matrix-data.txt", true)) { // Load Matrix 2 with reversed rows
        return 1; // Exit if file cannot be opened
    }
    cout << "Matrix 2:" << endl;
    mat2.display(); // Display Matrix 2

    // Add Matrix 1 and Matrix 2
    Matrix sum = mat1 + mat2; // Use overloaded + operator
    cout << "Sum of matrices:" << endl;
    sum.display(); // Display the sum of matrices

    // Multiply Matrix 1 and Matrix 2
    Matrix product = mat1 * mat2; // Use overloaded * operator
    cout << "Product of matrices:" << endl;
    product.display(); // Display the product of matrices

    // Calculate and display the sum of diagonal elements for Matrix 1
    cout << "Sum of diagonals of Matrix 1: " << mat1.sumOfDiagonals() << endl;

    // Swap rows 0 and 2 of Matrix 1 and display the result
    mat1.swapRows(0, 2);
    cout << "Matrix 1 after swapping rows:" << endl;
    mat1.display();

    return 0;
}
