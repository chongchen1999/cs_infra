#include <stdio.h>
#include "include/static_lib.h"
#include "include/shared_lib.h"

int main(int argc, char *argv[]) {
    int input_value = 10;
    int static_result, shared_result;
    
    printf("=== C Library Demo ===\n");
    printf("Demonstrating static and dynamic linking mechanisms\n\n");
    
    /* Display library information */
    printf("Static Library: %s\n", static_lib_info());
    printf("Shared Library: %s\n\n", shared_lib_info());
    
    /* Use the static library function */
    printf("Calling function from statically linked library:\n");
    static_result = static_operation(input_value);
    printf("Result from static library: %d\n\n", static_result);
    
    /* Use the shared library function */
    printf("Calling function from dynamically linked library:\n");
    shared_result = shared_operation(input_value);
    printf("Result from shared library: %d\n\n", shared_result);
    
    /* Compare the results */
    printf("Summary:\n");
    printf("- Input value: %d\n", input_value);
    printf("- Static library result (x2): %d\n", static_result);
    printf("- Shared library result (x3): %d\n", shared_result);
    
    return 0;
}