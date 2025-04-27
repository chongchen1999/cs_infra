#include "../include/basic_math.h"

double add(double a, double b) {
    DEBUG_PRINT("Adding %f and %f\n", a, b);
    return a + b;
}

double subtract(double a, double b) {
    DEBUG_PRINT("Subtracting %f from %f\n", b, a);
    return a - b;
}

double multiply(double a, double b) {
    DEBUG_PRINT("Multiplying %f by %f\n", a, b);
    return a * b;
}

int divide(double a, double b, double *result) {
    DEBUG_PRINT("Dividing %f by %f\n", a, b);

    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (b == 0) {
        return ERROR_DIVISION_BY_ZERO;
    }

    *result = a / b;
    return SUCCESS;
}

double power(double base, double exponent) {
    DEBUG_PRINT("Calculating %f raised to %f\n", base, exponent);
    return pow(base, exponent);
}

double square_root(double x) {
    DEBUG_PRINT("Calculating square root of %f\n", x);
    return sqrt(x);
}