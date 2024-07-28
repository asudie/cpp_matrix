#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

constexpr double kEps = 1e-7;

#include <cmath>
#include <stdexcept>

class S21Matrix {
 public:
  // METHODS

  // A basic constructor that initialises a matrix of some
  // predefined dimension
  S21Matrix();

  // Destructor
  ~S21Matrix();

  // Parametrized constructor with number of rows and
  // columns
  S21Matrix(int rows, int cols);

  // Copy constructor
  S21Matrix(const S21Matrix& other);

  // Move constructor
  S21Matrix(S21Matrix&& other);

  int GetRows() const { return rows_; };
  int GetCols() const { return cols_; };
  double GetElement(int r, int c) { return matrix_[r][c]; }
  const double GetElement(int r, int c) const { return matrix_[r][c]; }

  void SetRows(int r);
  void SetCols(int c);
  void SetElement(int r, int c, double value) { matrix_[r][c] = value; }

  S21Matrix& operator+=(const S21Matrix& rhs);
  S21Matrix& operator-=(const S21Matrix& rhs);
  S21Matrix& operator=(const S21Matrix& rhs);

  double& operator()(int row, int col) { return matrix_[row][col]; }
  const double& operator()(int row, int col) const { return matrix_[row][col]; }

  S21Matrix& operator*=(const S21Matrix& rhs);
  S21Matrix operator+(const S21Matrix& rhs) const;
  bool operator==(const S21Matrix& rhs) const;
  S21Matrix operator-(const S21Matrix& rhs) const;
  S21Matrix operator*(const S21Matrix& rhs) const;
  S21Matrix operator*(const double kNum) const;

  friend S21Matrix operator*(const double kNum, const S21Matrix& rhs);

  // Operations

  // Adds the second matrix to the current one
  void SumMatrix(const S21Matrix& other);

  // Checks matrices for equality with each other
  bool EqMatrix(const S21Matrix& other) const;

  // Subtracts another matrix from the current one
  void SubMatrix(const S21Matrix& other);

  // Multiplies the current matrix by a number
  void MulNumber(const double num);

  // Multiplies the current matrix by the second matrix
  void MulMatrix(const S21Matrix& other);

  S21Matrix Transpose() const;

  // Calculates the algebraic addition matrix of the current one and returns it
  // the matrix is not square
  S21Matrix CalcComplements() const;

  // Calculates and returns the determinant of the current matrix
  double Determinant() const;

  // Calculates and returns the inverse matrix
  S21Matrix InverseMatrix() const;

 private:
  void DeleteMatrix();
  S21Matrix Minor(int i, int j) const;

  // Attributes

  // Rows and columns
  int rows_, cols_;

  // Pointer to the memory where the matrix is allocated
  double** matrix_;
};

#endif  //  S21_MATRIX_OOP_H_
