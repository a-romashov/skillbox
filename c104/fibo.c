#include "stdio.h"
#include "fibo.h"

void printFibonacci() {
    static unsigned int prev = 0;
    static unsigned int prevPrev = 1;

    prev = prev + prevPrev;
    prevPrev = prev - prevPrev;

    if (prev < FIBONACCI_PRINT_UNTIL) {
        printf("%d ", prev);
        printFibonacci(FIBONACCI_PRINT_UNTIL);
    } else {
        printf("%d\n", prev);
        prev = 0;
        prevPrev = 1;
    }
}
