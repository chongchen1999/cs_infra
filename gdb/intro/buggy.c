// buggy.c
#include <stdio.h>

int main() {
    char *ptr = NULL;
    printf("About to crash...\n");
    *ptr = 'x';  // This will cause a segmentation fault
    return 0;
}