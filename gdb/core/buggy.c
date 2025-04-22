// buggy.c
#include <stdio.h>

void crash_function() {
    char *ptr = NULL;
    // This will cause a segmentation fault
    *ptr = 'x';
}

int main() {
    printf("About to crash...\n");
    crash_function();
    printf("This will never be printed\n");
    return 0;
}