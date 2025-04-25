#include <limits.h>
#include <stdio.h>
int cmp(int x) {
    return (x + 1) > x;
}

int main() {
    printf("INT_MAX = %d, cmp: %d\n", INT_MAX, (INT_MAX + 1) > INT_MAX,
           cmp(INT_MAX));
    return 0;
}