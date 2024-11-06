#include "sapper.h"
#include "stdlib.h"
#include "stdio.h"
#include "../lib/safeinput/SafeInput.h"

unsigned int **generateField(const unsigned int size, const unsigned int min, const unsigned int max) {
    unsigned int **result = (unsigned int **) malloc(sizeof(int **) * size);
    for (int i = 0; i < size; i++) {
        result[i] = (unsigned int *) malloc(sizeof(unsigned int *) * size);
        for (int j = 0; j < size; j++) {
            unsigned int val = rand() % (max + 1);
            result[i][j] = val < min ? min : val;
        }
    }
    return result;
}

void printField(unsigned int **field, unsigned int **opened, const unsigned int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            j && printf("\t");
            printf(
                opened[i][j] ? "%d" : "*",
                field[i][j]
            );
        }
        printf("\n");
    }
}

void sapperGame() {
    unsigned int **field = generateField(FIELD_SIZE, FIELD_MIN_VALUE, FIELD_MAX_VALUE);
    unsigned int **opened = generateField(FIELD_SIZE, 0, 0);
    unsigned int openedCount = 0; //cached array sum
    for (int i = 0; i < FIELD_SIZE; i++)
        for (int j = 0; j < FIELD_SIZE; j++)
            opened[i][j] = 0;

    printf(
        "Welcome to sapper game!\nTry guess all integers in field.\nValues can be between %d and %d\n",
        FIELD_MIN_VALUE,
        FIELD_MAX_VALUE
        );
    while (openedCount != FIELD_SIZE * FIELD_SIZE) {
        printField(field, opened, FIELD_SIZE);

        int choice = 0;

        scanInteger("%d", &choice, "Wrong value. Enter a valid integer\n");

        for (int i = 0; i < FIELD_SIZE; i++) {
            for (int j = 0; j < FIELD_SIZE; j++) {
                unsigned int fieldVal = field[i][j];
                if (choice == fieldVal) {
                    if (!opened[i][j]) {
                        opened[i][j] = 1;
                        openedCount++;
                    }
                }
            }
        }
    }
    printField(field, opened, FIELD_SIZE);
    printf("Game over!\n");
    for (int i = 0; i < FIELD_SIZE; i++) {
        free(field[i]);
        free(opened[i]);
    }
    free(field);
    free(opened);
}
