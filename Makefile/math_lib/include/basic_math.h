#ifndef BASIC_MATH_H
#define BASIC_MATH_H

#include "common.h"

// Function prototypes for basic math operations
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
int divide(double a, double b, double *result);
double power(double base, double exponent);
double square_root(double x);

#endif  // BASIC_MATH_H