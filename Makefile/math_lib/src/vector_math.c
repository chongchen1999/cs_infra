#include "../include/vector_math.h"

int vector_create(int size, Vector *result) {
    DEBUG_PRINT("Creating vector of size %d\n", size);

    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (size <= 0) {
        return ERROR_INVALID_DIMENSION;
    }

    result->size = size;
    result->data = (double *)malloc(size * sizeof(double));

    if (result->data == NULL) {
        return ERROR_NULL_POINTER;
    }

    // Initialize to zeros
    for (int i = 0; i < size; i++) {
        result->data[i] = 0.0;
    }

    return SUCCESS;
}

void vector_free(Vector *v) {
    DEBUG_PRINT("Freeing vector\n");

    if (v != NULL && v->data != NULL) {
        free(v->data);
        v->data = NULL;
        v->size = 0;
    }
}

int vector_add(const Vector *v1, const Vector *v2, Vector *result) {
    DEBUG_PRINT("Adding vectors\n");

    if (v1 == NULL || v2 == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (v1->size != v2->size) {
        return ERROR_INVALID_DIMENSION;
    }

    int status = vector_create(v1->size, result);
    if (status != SUCCESS) {
        return status;
    }

    for (int i = 0; i < v1->size; i++) {
        result->data[i] = v1->data[i] + v2->data[i];
    }

    return SUCCESS;
}

int vector_subtract(const Vector *v1, const Vector *v2, Vector *result) {
    DEBUG_PRINT("Subtracting vectors\n");

    if (v1 == NULL || v2 == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (v1->size != v2->size) {
        return ERROR_INVALID_DIMENSION;
    }

    int status = vector_create(v1->size, result);
    if (status != SUCCESS) {
        return status;
    }

    for (int i = 0; i < v1->size; i++) {
        result->data[i] = v1->data[i] - v2->data[i];
    }

    return SUCCESS;
}

int vector_scale(const Vector *v, double scalar, Vector *result) {
    DEBUG_PRINT("Scaling vector by %f\n", scalar);

    if (v == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    int status = vector_create(v->size, result);
    if (status != SUCCESS) {
        return status;
    }

    for (int i = 0; i < v->size; i++) {
        result->data[i] = v->data[i] * scalar;
    }

    return SUCCESS;
}

int vector_dot_product(const Vector *v1, const Vector *v2, double *result) {
    DEBUG_PRINT("Calculating dot product\n");

    if (v1 == NULL || v2 == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (v1->size != v2->size) {
        return ERROR_INVALID_DIMENSION;
    }

    *result = 0.0;
    for (int i = 0; i < v1->size; i++) {
        *result += v1->data[i] * v2->data[i];
    }

    return SUCCESS;
}

int vector_magnitude(const Vector *v, double *result) {
    DEBUG_PRINT("Calculating vector magnitude\n");

    if (v == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    double sum = 0.0;
    for (int i = 0; i < v->size; i++) {
        sum += v->data[i] * v->data[i];
    }

    *result = sqrt(sum);
    return SUCCESS;
}

int vector_normalize(const Vector *v, Vector *result) {
    DEBUG_PRINT("Normalizing vector\n");

    if (v == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    double magnitude;
    int status = vector_magnitude(v, &magnitude);

    if (status != SUCCESS) {
        return status;
    }

    if (magnitude == 0) {
        return ERROR_DIVISION_BY_ZERO;
    }

    return vector_scale(v, 1.0 / magnitude, result);
}