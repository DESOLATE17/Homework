#include "matrix.h"
#include "exceptions.h"
#include <string>
#include <iomanip>
#include <limits>
#include <cmath>
#include <cstring>
#include <fstream>

namespace prep {

    Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        matrix = nullptr;
        if (rows != 0 && cols!= 0) {
            matrix = new double *[rows];
            for (size_t i = 0; i < rows; ++i) {
                matrix[i] = new double[cols] {0};
            }
        }
    }

    Matrix::~Matrix() {
        if (matrix != nullptr) {
            for (size_t i = 0; i < rows; ++i) {
                delete [] matrix[i];
            }
            delete [] matrix;
        }
    }

    Matrix& Matrix::operator=(const Matrix& rhs) {
        if (this != &rhs) {
        if (rows != 0 && cols != 0 && matrix != nullptr) {
        for (size_t i = 0; i < rows; ++i) {
            delete [] matrix[i];
        }
        delete [] matrix;
        }
        rows = rhs.rows;
        cols = rhs.cols;
        if (rows != 0 && cols!= 0) {
            matrix = new double *[rows];
            for (size_t i = 0; i < rows; ++i) {
                matrix[i] = new double[cols];
                for (size_t j = 0; j < cols; ++j) {
                    matrix[i][j] = rhs.matrix[i][j];
                }
            }
        } else {
            matrix = nullptr;
        }
        }
        return *this;
    }

    Matrix::Matrix(const Matrix& rhs) : Matrix(rhs.rows, rhs.cols) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                matrix[i][j] = rhs.matrix[i][j];
            }
        }
    }

    Matrix::Matrix(std::istream &is) {
        double value;
        is >> rows;
        if (!is) {
            throw InvalidMatrixStream();
        }
        is >> cols;
        if (!is) {
            throw InvalidMatrixStream();
        }
        if (rows != 0 && cols!= 0) {
            matrix = new double *[rows];
            for (size_t i = 0; i < rows; ++i) {
                matrix[i] = new double[cols] {0};
            }
        }
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                is >> value;
                if (!is) {
                    for (size_t k = 0; k < rows; ++k) {
                        delete [] matrix[k];
                    }
                    delete [] matrix;
                    matrix = nullptr;
                    throw InvalidMatrixStream();
                }
                matrix[i][j] = value;
            }
        }
    }


    size_t Matrix::getRows() const {
        return rows;
    }

    size_t Matrix::getCols() const {
        return cols;
    }


    double Matrix::operator()(size_t i, size_t j) const {
        if (i >= rows || j >= cols) {
            throw OutOfRange(i, j, *this);
        }
        return matrix[i][j];
    }

    double &Matrix::operator()(size_t i, size_t j) {
        if (i >= rows || j >= cols) {
            throw OutOfRange(i, j, *this);
        }
        return matrix[i][j];
    }

    bool Matrix::operator==(const Matrix &rhs) const {
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            return false;
        }
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (fabs(matrix[i][j] - rhs.matrix[i][j]) > 1.0e-7) {
                    return false;
                }
            }
        }
        return true;
    }


    bool Matrix::operator!=(const Matrix &rhs) const {
        return !(*this == rhs);
    }

    Matrix Matrix::operator+(const Matrix &rhs) const {
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            throw DimensionMismatch(*this, rhs);
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];
            }
        }
        return result;
    }

    Matrix Matrix::operator-(const Matrix &rhs) const {
        return *this + rhs * (-1);
    }

    Matrix Matrix::operator*(const Matrix &rhs) const {
        if (this->cols != rhs.rows) {
            throw DimensionMismatch(*this, rhs);
        }
        Matrix result(rows, rhs.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < rhs.cols; ++j) {
                result.matrix[i][j] = 0.0;
                for (size_t k = 0; k < cols; ++k) {
                    result.matrix[i][j] += matrix[i][k] * rhs.matrix[k][j];
                }
            }
        }
        return result;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.matrix[i][j] = this->matrix[i][j] * val;
            }
        }
        return result;
    }

    Matrix operator*(double val, const Matrix &matrix) {
        Matrix result(matrix.rows, matrix.cols);
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                result.matrix[i][j] = matrix.matrix[i][j] * val;
            }
        }
        return result;
    }

    std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
        os << matrix.rows << " " << matrix.cols << std::endl;
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                os << std::setprecision(std::numeric_limits<double>::max_digits10) << matrix.matrix[i][j];
                if (j != matrix.cols - 1) {
                    os << " ";
                } else {
                    os << std::endl;
                }
            }
        }
        return os;
    }

    Matrix Matrix::transp() const {
        Matrix result(cols, rows);
        for (size_t i = 0; i < cols; ++i) {
            for (size_t j = 0; j < rows; ++j) {
                result.matrix[i][j] = matrix[j][i];
            }
        }
        return result;
    }

    void Matrix::GetMatr(Matrix& new_matrix, size_t i, size_t j) const {
        size_t i_shift = 0;
        for (size_t new_i = 0; new_i < rows - 1; ++new_i) {
            if (new_i == i) {
                i_shift = 1;
            }
            size_t j_shift = 0;
            for (size_t new_j = 0; new_j < rows - 1; ++new_j) {
                if (new_j == j) {
                    j_shift = 1;
                }
                new_matrix.matrix[new_i][new_j] = matrix[new_i + i_shift][new_j +  j_shift];
            }
        }
    }

    double Matrix::det() const {
        if (rows != cols) {
            throw DimensionMismatch(*this);
        }
        double d = 0;
        Matrix new_matrix(rows - 1, rows - 1);
        if (rows == 1) {
            d = matrix[0][0];
            return(d);
        }
        if (rows == 2) {
            d = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
            return(d);
        }
        if (rows > 2) {
            double k = 1;
            for (size_t i = 0; i < rows; ++i) {
                this->GetMatr(new_matrix, i, 0);
                d += k * matrix[i][0] * new_matrix.det();
                k *= -1;
            }
        }
        return d;
    }


    Matrix Matrix::adj() const {
        if (rows != cols) {
            throw DimensionMismatch(*this);
        }
        Matrix result(rows, rows);
        Matrix new_matrix(rows - 1, rows - 1);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < rows; ++j) {
                this->GetMatr(new_matrix, i, j);
                double k = pow(-1, i + j);
                result.matrix[i][j] = k * new_matrix.det();
            }
        }
        return result.transp();
    }

    Matrix Matrix::inv() const {
        if (rows != cols) {
            throw DimensionMismatch(*this);
        }
        if (this->det() == 0) {
            throw SingularMatrix();
        }
        Matrix result(rows, rows);
        return 1/result.det() *  result.adj();
    }


}  //  namespace prep
