#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::~S21Matrix() { DeleteMatrix(); }

void S21Matrix::DeleteMatrix() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("invalid parameters for matrix");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(0), cols_(0), matrix_(nullptr) {
  *this = other;
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_) {
  other.cols_ = 0;
  other.rows_ = 0;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.GetRows() || cols_ != other.GetCols()) {
    throw std::invalid_argument("Matrices are of different dimensions");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->SetElement(i, j, matrix_[i][j] + other.matrix_[i][j]);
    }
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix &rhs) const {
  S21Matrix lhs = *this;
  lhs.SumMatrix(rhs);
  return lhs;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool result = true;
  if (rows_ == other.GetRows() && cols_ == other.GetCols()) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) < kEps) {
          continue;
        } else {
          result = false;
        }
      }
    }
  } else {
    result = false;
  }
  return result;
}

bool S21Matrix::operator==(const S21Matrix &rhs) const {
  bool res = EqMatrix(rhs);
  return res;
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.GetRows() || cols_ != other.GetCols()) {
    throw std::invalid_argument("Matrices are of different dimensions");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->SetElement(i, j, matrix_[i][j] - other.matrix_[i][j]);
    }
  }
}

S21Matrix S21Matrix::operator-(const S21Matrix &rhs) const {
  S21Matrix lhs = *this;
  lhs.SubMatrix(rhs);
  return lhs;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &rhs) {
  this->SumMatrix(rhs);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &rhs) {
  this->SubMatrix(rhs);
  return *this;
}

void S21Matrix::MulNumber(const double num) {
  if (num != num) {
    throw std::invalid_argument("invalid parameters");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->SetElement(i, j, matrix_[i][j] * num);
    }
  }
}

S21Matrix operator*(const double kNum, const S21Matrix &rhs) {
  S21Matrix lhs = rhs;
  lhs.MulNumber(kNum);
  return lhs;
}

S21Matrix S21Matrix::operator*(const double kNum) const {
  S21Matrix lhs = *this;
  lhs.MulNumber(kNum);
  return lhs;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.GetRows()) {
    throw std::invalid_argument("Can't calculate");
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.GetCols(); j++) {
      for (int k = 0; k < cols_; k++) {
        res.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = res;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &rhs) {
  if (this != &rhs) {
    DeleteMatrix();
    rows_ = rhs.GetRows();
    cols_ = rhs.GetCols();
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        this->matrix_[i][j] = rhs.GetElement(i, j);
      }
    }
  }

  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &rhs) const {
  S21Matrix lhs = *this;
  lhs.MulMatrix(rhs);
  return lhs;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &rhs) {
  this->MulMatrix(rhs);
  return *this;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix res(cols_, rows_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}

S21Matrix S21Matrix::Minor(int i, int j) const {
  if (i >= rows_ || j >= cols_ || rows_ == 1 || cols_ == 1) {
    throw std::invalid_argument("invalid parameters for matrix");
  }
  S21Matrix res(rows_ - 1, cols_ - 1);
  if (i < rows_ && j < cols_) {
    for (int a = 0, k = 0; a < rows_ && k < (rows_ - 1); a++, k++) {
      for (int b = 0, y = 0; b < cols_ && y < (cols_ - 1); b++, y++) {
        if (a == i) {
          a++;
        }
        if (b == j) {
          b++;
        }
        res.matrix_[k][y] = matrix_[a][b];
      }
    }
  }
  return res;
}

double S21Matrix::Determinant() const {
  double result = 0.0;
  if (rows_ != cols_) {
    throw std::invalid_argument("Can't calculate");
  }
  if (rows_ == 1) {
    return result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor_m = this->Minor(0, j);
      double temp_result = minor_m.Determinant();
      int sign = (j & 1) ? -1 : 1;
      result += matrix_[0][j] * temp_result * sign;
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Can't calculate");
  }
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor_m = this->Minor(i, j);
      double temp_result = minor_m.Determinant();
      int sign = ((i + j) & 1) ? -1 : 1;
      res.matrix_[i][j] = temp_result * sign;
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (!this->Determinant()) {
    throw std::invalid_argument("Can't calculate");
  }
  S21Matrix comp_result = this->CalcComplements();
  S21Matrix trans_result = comp_result.Transpose();
  trans_result.MulNumber(1 / this->Determinant());
  return trans_result;
}

void S21Matrix::SetRows(int r) {
  if (r <= 0) throw std::invalid_argument("Can't set");
  S21Matrix temp(r, cols_);
  for (int i = 0; i < std::min(rows_, r); i++) {
    for (int j = 0; j < cols_; j++) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = temp;
}

void S21Matrix::SetCols(int c) {
  if (c <= 0) throw std::invalid_argument("Can't set");
  S21Matrix temp(rows_, c);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < std::min(cols_, c); j++) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = temp;
}
