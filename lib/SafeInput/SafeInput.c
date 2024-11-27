#include "SafeInput.h"
#include <stdio.h>
#define SAFE_SCAN_BUFFER_SIZE 50


void scanInteger(const char *mask, int *result, const char *errorMessage) {
    char buffer[SAFE_SCAN_BUFFER_SIZE];
    fgets(buffer, SAFE_SCAN_BUFFER_SIZE, stdin);

    while (!sscanf(buffer, mask, result)) {
        printf("%s", errorMessage);
        fgets(buffer, SAFE_SCAN_BUFFER_SIZE, stdin);
    }
}
