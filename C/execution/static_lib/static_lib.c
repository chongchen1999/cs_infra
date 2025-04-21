#include "../include/static_lib.h"
#include <stdio.h>

/* 
 * Static variable that is only visible within this file
 * This demonstrates variable scope within a static library
 */
static const char* library_version = "Static Library v1.0";

/* Implementation of the static_operation function */
int static_operation(int value) {
    printf("[Static Library] Performing operation on value: %d\n", value);
    return value * 2; // Simply double the input value
}

/* Implementation of the static_lib_info function */
const char* static_lib_info(void) {
    return library_version;
}