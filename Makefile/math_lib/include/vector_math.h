#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

#include "common.h"

// Vector struct definition
typedef struct {
    int size;
    double *data;
} Vector;

// Function prototypes for vector operations
int vector_create(int size, Vector *result);
void vector_free(Vector *v);
int vector_add(const Vector *v1, const Vector *v2, Vector *result);
int vector_subtract(const Vector *v1, const Vector *v2, Vector *result);
int vector_scale(const Vector *v, double scalar, Vector *result);
int vector_dot_product(const Vector *v1, const Vector *v2, double *result);
int vector_magnitude(const Vector *v, double *result);
int vector_normalize(const Vector *v, Vector *result);

#endif  // VECTOR_MATH_H