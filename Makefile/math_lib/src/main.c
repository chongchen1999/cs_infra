#include <stdio.h>

#include "../include/basic_math.h"
#include "../include/matrix_math.h"
#include "../include/vector_math.h"

void test_basic_math() {
    printf("\n===== Basic Math Tests =====\n");

    printf("Addition: 5 + 3 = %.2f\n", add(5, 3));
    printf("Subtraction: 5 - 3 = %.2f\n", subtract(5, 3));
    printf("Multiplication: 5 * 3 = %.2f\n", multiply(5, 3));

    double result;
    int status = divide(10, 2, &result);
    if (status == SUCCESS) {
        printf("Division: 10 / 2 = %.2f\n", result);
    } else {
        printf("Division error: %d\n", status);
    }

    printf("Power: 2^3 = %.2f\n", power(2, 3));
    printf("Square Root: sqrt(16) = %.2f\n", square_root(16));
}

void test_vector_operations() {
    printf("\n===== Vector Operations Tests =====\n");

    Vector v1, v2, v3;
    double scalar_result;

    // Create vectors
    vector_create(3, &v1);
    vector_create(3, &v2);

    // Initialize values
    v1.data[0] = 1.0;
    v1.data[1] = 2.0;
    v1.data[2] = 3.0;
    v2.data[0] = 4.0;
    v2.data[1] = 5.0;
    v2.data[2] = 6.0;

    printf("Vector 1: [%.2f, %.2f, %.2f]\n", v1.data[0], v1.data[1],
           v1.data[2]);
    printf("Vector 2: [%.2f, %.2f, %.2f]\n", v2.data[0], v2.data[1],
           v2.data[2]);

    // Vector addition
    vector_add(&v1, &v2, &v3);
    printf("Vector Addition: [%.2f, %.2f, %.2f]\n", v3.data[0], v3.data[1],
           v3.data[2]);
    vector_free(&v3);

    // Vector subtraction
    vector_subtract(&v1, &v2, &v3);
    printf("Vector Subtraction: [%.2f, %.2f, %.2f]\n", v3.data[0], v3.data[1],
           v3.data[2]);
    vector_free(&v3);

    // Vector scaling
    vector_scale(&v1, 2.0, &v3);
    printf("Vector Scaling (x2): [%.2f, %.2f, %.2f]\n", v3.data[0], v3.data[1],
           v3.data[2]);
    vector_free(&v3);

    // Vector dot product
    vector_dot_product(&v1, &v2, &scalar_result);
    printf("Vector Dot Product: %.2f\n", scalar_result);

    // Vector magnitude
    vector_magnitude(&v1, &scalar_result);
    printf("Vector 1 Magnitude: %.2f\n", scalar_result);

    // Vector normalization
    vector_normalize(&v1, &v3);
    printf("Vector 1 Normalized: [%.2f, %.2f, %.2f]\n", v3.data[0], v3.data[1],
           v3.data[2]);

    // Cleanup
    vector_free(&v1);
    vector_free(&v2);
    vector_free(&v3);
}

void test_matrix_operations() {
    printf("\n===== Matrix Operations Tests =====\n");

    Matrix m1, m2, m3;
    Vector v1, v2;
    double scalar_result;

    // Create matrices
    matrix_create(2, 3, &m1);
    matrix_create(3, 2, &m2);

    // Initialize matrix values
    m1.data[0][0] = 1.0;
    m1.data[0][1] = 2.0;
    m1.data[0][2] = 3.0;
    m1.data[1][0] = 4.0;
    m1.data[1][1] = 5.0;
    m1.data[1][2] = 6.0;

    m2.data[0][0] = 7.0;
    m2.data[0][1] = 8.0;
    m2.data[1][0] = 9.0;
    m2.data[1][1] = 10.0;
    m2.data[2][0] = 11.0;
    m2.data[2][1] = 12.0;

    printf("Matrix 1:\n");
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            printf("%.2f ", m1.data[i][j]);
        }
        printf("\n");
    }

    printf("Matrix 2:\n");
    for (int i = 0; i < m2.rows; i++) {
        for (int j = 0; j < m2.cols; j++) {
            printf("%.2f ", m2.data[i][j]);
        }
        printf("\n");
    }

    // Matrix multiplication
    matrix_multiply(&m1, &m2, &m3);
    printf("Matrix Multiplication:\n");
    for (int i = 0; i < m3.rows; i++) {
        for (int j = 0; j < m3.cols; j++) {
            printf("%.2f ", m3.data[i][j]);
        }
        printf("\n");
    }
    matrix_free(&m3);

    // Create square matrix for determinant
    matrix_free(&m1);
    matrix_create(3, 3, &m1);
    m1.data[0][0] = 1.0;
    m1.data[0][1] = 2.0;
    m1.data[0][2] = 3.0;
    m1.data[1][0] = 4.0;
    m1.data[1][1] = 5.0;
    m1.data[1][2] = 6.0;
    m1.data[2][0] = 7.0;
    m1.data[2][1] = 8.0;
    m1.data[2][2] = 9.0;

    printf("3x3 Matrix:\n");
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            printf("%.2f ", m1.data[i][j]);
        }
        printf("\n");
    }

    // Matrix determinant
    matrix_determinant(&m1, &scalar_result);
    printf("Matrix Determinant: %.2f\n", scalar_result);

    // Matrix transpose
    matrix_transpose(&m1, &m3);
    printf("Matrix Transpose:\n");
    for (int i = 0; i < m3.rows; i++) {
        for (int j = 0; j < m3.cols; j++) {
            printf("%.2f ", m3.data[i][j]);
        }
        printf("\n");
    }

    // Create vector for matrix-vector multiplication
    vector_create(3, &v1);
    v1.data[0] = 1.0;
    v1.data[1] = 2.0;
    v1.data[2] = 3.0;

    // Matrix-vector multiplication
    matrix_vector_multiply(&m1, &v1, &v2);
    printf("Matrix-Vector Multiplication: [%.2f, %.2f, %.2f]\n", v2.data[0],
           v2.data[1], v2.data[2]);

    // Cleanup
    matrix_free(&m1);
    matrix_free(&m2);
    matrix_free(&m3);
    vector_free(&v1);
    vector_free(&v2);
}

int main() {
    printf("Math Library Demo\n");
    printf("================\n");

    test_basic_math();
    test_vector_operations();
    test_matrix_operations();

    printf("\nAll tests completed successfully!\n");
    return 0;
}