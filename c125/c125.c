#include "stdio.h"
#include "../lib/SafeInput/SafeInput.h"

void printInts(const int* array, const unsigned int size) {
    for (int i = 0; i < size; i++) {
        printf("%d\n", *(array + i));
    }
}

#define ACT 0
#if ACT
#include "stdlib.h"
int* getIntArr(const unsigned int size) {

    int *arr = calloc(size, sizeof(int*));
    for (int i = 0; i < size; i++) {
        scanInteger("%d", arr + i, "try again\n");
    }
    printInts(arr, size);
    free(arr);
    return arr;
}
#else
int* getIntArr(const unsigned int size) {
    int arr[size];
    for (int i = 0; i < size; i++) {
        scanInteger("%d", arr + i, "try again\n");
    }
    printInts(arr, size);
    return arr;
}
#endif

int main() {
    int size;
    scanInteger("%d", &size, "try again\n");
    int* arr = getIntArr(size);
    printInts(arr, size);
}
