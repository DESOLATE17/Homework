#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file) {
    FILE* file = fopen(path_file, "r+");
    Matrix * matrix = (Matrix *)calloc(1, sizeof(Matrix));
    if (file == NULL) {
        perror("error opening file");
        free(matrix);
        return NULL;
    } else {
        fscanf(file, "%zu%zu", &matrix->rows, &matrix->cols);
        if (matrix->cols == 0 || matrix->rows == 0) {
            puts("wrong size");
            free(matrix);
            fclose(file);
            return NULL;
        } else {
            if ((matrix->matrix = (double **)calloc(matrix->rows, sizeof(double *))) == NULL) {
                puts("allocation error");
                free(matrix);
                fclose(file);
                return NULL;
            } else {
            for (size_t i = 0; i < matrix->rows; ++i) {
                    if ((matrix->matrix[i] = (double *)calloc((matrix->cols), sizeof(double))) == NULL) {
                        puts("allocation error");
                        matrix->rows = i;
                        free_matrix(matrix);
                        fclose(file);
                        return NULL;
                    }
                    for (size_t j = 0; j < matrix->cols; ++j) {
                        fscanf(file, "%lf", &matrix->matrix[i][j]);
                    }
                }
            }
            fclose(file);
        }
    }
    return matrix;
}

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix * matrix;
    if ((matrix = (Matrix *)calloc(1, sizeof(Matrix))) == NULL) {
        puts("error");
        return NULL;
    } else {
    if (rows == 0 || cols == 0) {
        puts("wrong size");
        free(matrix);
        return NULL;
    } else {
        if ((matrix->matrix = (double **)calloc(rows, sizeof(double *))) == NULL) {
            puts("allocation error");
            free(matrix);
            return NULL;
        } else {
            for (size_t i = 0; i < rows; ++i) {
                if ((matrix->matrix[i] = (double *)calloc(cols, sizeof(double))) == NULL) {
                    puts("allocation error");
                    matrix->rows = i;
                    free_matrix(matrix);
                    return NULL;
                }
            }
        }
        matrix->rows = rows;
        matrix->cols = cols;
        }
    }
    return matrix;
}

void free_matrix(Matrix* matrix) {
    for (size_t i = 0; i < matrix->rows; ++i) {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
    free(matrix);
}

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows) {
    if (matrix == NULL || rows == NULL) {
        return 1;
    }
    *rows = matrix->rows;
    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    if (matrix == NULL || cols == NULL) {
        return 1;
    }
    *cols = matrix->cols;
    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (matrix == NULL || val == NULL || matrix->matrix == NULL || row >= matrix->rows ||
     col >= matrix->cols) {
        return 1;
    }
    *val = matrix->matrix[row][col];
    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (matrix == NULL || matrix->matrix == NULL || row >= matrix->rows || col >= matrix->cols) {
        return 1;
    }
    matrix->matrix[row][col] = val;
    return 0;
}

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (matrix == NULL) {
        puts("wrong parameters");
        return NULL;
    }
    Matrix * new_matrix = create_matrix(matrix->rows, matrix->cols);
    if (new_matrix != NULL) {
        for (size_t i = 0; i < matrix->rows; ++i) {
            for (size_t j = 0; j < matrix->cols; ++j) {
                new_matrix->matrix[i][j] = matrix->matrix[i][j] * val;
            }
        }
    }
    return new_matrix;
}

Matrix* transp(const Matrix* matrix) {
    if (matrix == NULL) {
        puts("wrong parameters");
        return NULL;
    }
    Matrix * transp_matrix = create_matrix(matrix->cols, matrix->rows);
    if (transp_matrix != NULL) {
        for (size_t i = 0; i < matrix->cols; ++i) {
            for (size_t j = 0; j < matrix->rows; ++j) {
                transp_matrix->matrix[i][j] = matrix->matrix[j][i];
            }
        }
    }
    return transp_matrix;
}
Matrix* sum(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL || (l->cols != r->cols) || (l->rows != r->rows)) {
        puts("wrong parameters");
        return NULL;
    }
    Matrix * result = create_matrix(l->rows, l->cols);
    if (result != NULL) {
        for (size_t i = 0; i < result->rows; ++i) {
            for (size_t j = 0; j < result->cols; ++j) {
                result->matrix[i][j] = l->matrix[i][j] + r->matrix[i][j];
            }
        }
    }
    return result;
}
Matrix* sub(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL || (l->cols != r->cols) || (l->rows != r->rows)) {
        puts("wrong parameters");
        return NULL;
    }
    Matrix * new_r = mul_scalar(r, -1);
    Matrix * result = sum(l, new_r);
    free_matrix(new_r);
    return result;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL || (l->cols != r->rows)) {
        puts("wrong parameters");
        return NULL;
    }
    Matrix * result = create_matrix(l->rows, r->cols);
    if (result != NULL) {
        for (size_t i = 0; i < l->rows; ++i) {
            for (size_t j = 0; j < r->cols; ++j) {
                result->matrix[i][j] = 0;
                for (size_t k = 0; k < l->cols; ++k) {
                    result->matrix[i][j] += l->matrix[i][k] * r->matrix[k][j];
                }
            }
        }
    }
    return result;
}

// Extra operations
// int det(const Matrix* matrix, double* val);
// Matrix* adj(const Matrix* matrix);
// Matrix* inv(const Matrix* matrix);

