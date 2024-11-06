#define ACTION_FIBONACCI_PRINT 1
#define ACTION_SAPPER_GAME 2

#define CURRENT_ACTION ACTION_SAPPER_GAME

#ifdef CURRENT_ACTION

#if CURRENT_ACTION == ACTION_FIBONACCI_PRINT

#include "fibo.h"
#define ACTION printFibonacci()

#elif CURRENT_ACTION == ACTION_SAPPER_GAME

#include "sapper.h"
#define ACTION sapperGame()

#else
#define ACTION printf("Fatal. Action not found.\n")
#endif

#else
#define ACTION printf("Fatal. Action not defined.\n")
#endif
#include <stdio.h>

void main() {
    ACTION;
}
