#ifndef COMMON_H
#define COMMON_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Define error codes
#define SUCCESS 0
#define ERROR_NULL_POINTER -1
#define ERROR_DIVISION_BY_ZERO -2
#define ERROR_INVALID_DIMENSION -3

// Debug macro
#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) printf("DEBUG: " fmt, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

#endif  // COMMON_H