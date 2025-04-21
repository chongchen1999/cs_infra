#ifndef STATIC_LIB_H
#define STATIC_LIB_H

/**
 * Performs a simple operation and returns the result
 * This function is implemented in a static library
 */
int static_operation(int value);

/**
 * Returns information about the static library
 */
const char* static_lib_info(void);

#endif /* STATIC_LIB_H */