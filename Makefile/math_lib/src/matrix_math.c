#include "../include/matrix_math.h"

int matrix_create(int rows, int cols, Matrix *result) {
    DEBUG_PRINT("Creating %dx%d matrix\n", rows, cols);

    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (rows <= 0 || cols <= 0) {
        return ERROR_INVALID_DIMENSION;
    }

    result->rows = rows;
    result->cols = cols;

    // Allocate memory for rows
    result->data = (double **)malloc(rows * sizeof(double *));
    if (result->data == NULL) {
        return ERROR_NULL_POINTER;
    }

    // Allocate memory for columns
    for (int i = 0; i < rows; i++) {
        result->data[i] = (double *)malloc(cols * sizeof(double));
        if (result->data[i] == NULL) {
            // Free already allocated memory
            for (int j = 0; j < i; j++) {
                free(result->data[j]);
            }
            free(result->data);
            result->data = NULL;
            return ERROR_NULL_POINTER;
        }

        // Initialize to zeros
        for (int j = 0; j < cols; j++) {
            result->data[i][j] = 0.0;
        }
    }

    return SUCCESS;
}

void matrix_free(Matrix *m) {
    DEBUG_PRINT("Freeing matrix\n");

    if (m == NULL || m->data == NULL) {
        return;
    }

    for (int i = 0; i < m->rows; i++) {
        if (m->data[i] != NULL) {
            free(m->data[i]);
        }
    }

    free(m->data);
    m->data = NULL;
    m->rows = 0;
    m->cols = 0;
}

int matrix_add(const Matrix *m1, const Matrix *m2, Matrix *result) {
    DEBUG_PRINT("Adding matrices\n");

    if (m1 == NULL || m2 == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        return ERROR_INVALID_DIMENSION;
    }

    int status = matrix_create(m1->rows, m1->cols, result);
    if (status != SUCCESS) {
        return status;
    }

    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            result->data[i][j] = m1->data[i][j] + m2->data[i][j];
        }
    }

    return SUCCESS;
}

int matrix_subtract(const Matrix *m1, const Matrix *m2, Matrix *result) {
    DEBUG_PRINT("Subtracting matrices\n");

    if (m1 == NULL || m2 == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        return ERROR_INVALID_DIMENSION;
    }

    int status = matrix_create(m1->rows, m1->cols, result);
    if (status != SUCCESS) {
        return status;
    }

    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            result->data[i][j] = m1->data[i][j] - m2->data[i][j];
        }
    }

    return SUCCESS;
}

int matrix_multiply(const Matrix *m1, const Matrix *m2, Matrix *result) {
    DEBUG_PRINT("Multiplying matrices\n");

    if (m1 == NULL || m2 == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (m1->cols != m2->rows) {
        return ERROR_INVALID_DIMENSION;
    }

    int status = matrix_create(m1->rows, m2->cols, result);
    if (status != SUCCESS) {
        return status;
    }

    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m2->cols; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < m1->cols; k++) {
                result->data[i][j] += m1->data[i][k] * m2->data[k][j];
            }
        }
    }

    return SUCCESS;
}

int matrix_scale(const Matrix *m, double scalar, Matrix *result) {
    DEBUG_PRINT("Scaling matrix by %f\n", scalar);

    if (m == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    int status = matrix_create(m->rows, m->cols, result);
    if (status != SUCCESS) {
        return status;
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            result->data[i][j] = m->data[i][j] * scalar;
        }
    }

    return SUCCESS;
}

int matrix_transpose(const Matrix *m, Matrix *result) {
    DEBUG_PRINT("Transposing matrix\n");

    if (m == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    int status = matrix_create(m->cols, m->rows, result);
    if (status != SUCCESS) {
        return status;
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            result->data[j][i] = m->data[i][j];
        }
    }

    return SUCCESS;
}

int matrix_determinant(const Matrix *m, double *result) {
    DEBUG_PRINT("Calculating matrix determinant\n");

    if (m == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (m->rows != m->cols) {
        return ERROR_INVALID_DIMENSION;
    }

    // For simplicity, only implement 2x2 and 3x3 determinants
    if (m->rows == 2) {
        *result = m->data[0][0] * m->data[1][1] - m->data[0][1] * m->data[1][0];
        return SUCCESS;
    } else if (m->rows == 3) {
        *result = m->data[0][0] * (m->data[1][1] * m->data[2][2] -
                                   m->data[1][2] * m->data[2][1]) -
                  m->data[0][1] * (m->data[1][0] * m->data[2][2] -
                                   m->data[1][2] * m->data[2][0]) +
                  m->data[0][2] * (m->data[1][0] * m->data[2][1] -
                                   m->data[1][1] * m->data[2][0]);
        return SUCCESS;
    } else {
        return ERROR_INVALID_DIMENSION;  // Not implemented for larger matrices
    }
}

int matrix_vector_multiply(const Matrix *m, const Vector *v, Vector *result) {
    DEBUG_PRINT("Multiplying matrix by vector\n");

    if (m == NULL || v == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (m->cols != v->size) {
        return ERROR_INVALID_DIMENSION;
    }

    int status = vector_create(m->rows, result);
    if (status != SUCCESS) {
        return status;
    }

    for (int i = 0; i < m->rows; i++) {
        result->data[i] = 0;
        for (int j = 0; j < m->cols; j++) {
            result->data[i] += m->data[i][j] * v->data[j];
        }
    }

    return SUCCESS;
}