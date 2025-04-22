#include <stdio.h>

int main() {
    int counter = 0;

    printf("Initial counter value: %d\n", counter);

    for (int i = 0; i < 5; i++) {
        counter++;
        printf("Counter after increment %d: %d\n", i + 1, counter);
    }

    // Somewhere here the counter gets corrupted
    counter = 100;  // Let's pretend this is happening in a large codebase and
                    // we don't know where

    printf("Final counter value: %d\n", counter);
    return 0;
}