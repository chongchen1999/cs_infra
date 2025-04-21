#define BUILDING_SHARED_LIB
#include "../include/shared_lib.h"
#include <stdio.h>

/* 
 * Static variable that is only visible within this file
 * This demonstrates variable scope within a shared library
 */
static const char* library_version = "Shared Library v1.0";

/* Implementation of the shared_operation function */
int shared_operation(int value) {
    printf("[Shared Library] Performing operation on value: %d\n", value);
    return value * 3; // Triple the input value to differentiate from static lib
}

/* Implementation of the shared_lib_info function */
const char* shared_lib_info(void) {
    return library_version;
}

/*
 * Library initialization and cleanup functions
 * These are called automatically when the shared library is loaded/unloaded
 */
#ifndef _WIN32
__attribute__((constructor))
static void lib_init(void) {
    printf("[Shared Library] Initializing...\n");
}

__attribute__((destructor))
static void lib_fini(void) {
    printf("[Shared Library] Cleaning up...\n");
}
#endif