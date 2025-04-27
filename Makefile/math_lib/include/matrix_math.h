#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include "common.h"
#include "vector_math.h"

// Matrix struct definition
typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

// Function prototypes for matrix operations
int matrix_create(int rows, int cols, Matrix *result);
void matrix_free(Matrix *m);
int matrix_add(const Matrix *m1, const Matrix *m2, Matrix *result);
int matrix_subtract(const Matrix *m1, const Matrix *m2, Matrix *result);
int matrix_multiply(const Matrix *m1, const Matrix *m2, Matrix *result);
int matrix_scale(const Matrix *m, double scalar, Matrix *result);
int matrix_transpose(const Matrix *m, Matrix *result);
int matrix_determinant(const Matrix *m, double *result);
int matrix_vector_multiply(const Matrix *m, const Vector *v, Vector *result);

#endif  // MATRIX_MATH_H