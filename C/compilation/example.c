#include <stdio.h>
#define MAX 100

// A simple function to calculate factorial
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n-1);
}

int main() {
    printf("The factorial of 5 is: %d\n", factorial(5));
    printf("The maximum value is: %d\n", MAX);
    return 0;
}