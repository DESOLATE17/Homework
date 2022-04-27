#pragma once // NOLINT

#include <vector>
#include <istream>

namespace prep {
class Matrix {
  double** matrix;
  size_t rows;
  size_t cols;

 public:
  explicit Matrix(size_t rows = 0, size_t cols = 0);
  explicit Matrix(std::istream& is);
  Matrix(const Matrix& rhs);
  Matrix& operator=(const Matrix& rhs);
  ~Matrix();

  size_t getRows() const;
  size_t getCols() const;

  double operator()(size_t i, size_t j) const;
  double& operator()(size_t i, size_t j);

  bool operator==(const Matrix& rhs) const;
  bool operator!=(const Matrix& rhs) const;

  Matrix operator+(const Matrix& rhs) const;
  Matrix operator-(const Matrix& rhs) const;
  Matrix operator*(const Matrix& rhs) const;

  Matrix operator*(double val) const;

  friend
  Matrix operator*(double val, const Matrix& matrix);
  friend
  std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
  void GetMatr(Matrix& new_matrix, size_t i, size_t j) const;
  Matrix transp() const;
  double det() const;
  Matrix adj() const;
  Matrix inv() const;
};

Matrix operator*(double val, const Matrix& matrix);
std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
}  // namespace prep
