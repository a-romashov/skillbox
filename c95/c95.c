//
// Created by Андрей on 26.10.2024.
//
#include <stdio.h>
#include <stdlib.h>


void printFibonacci(unsigned int until);

void sapperGame(unsigned int size, unsigned int min, unsigned int max);

void main() {
    printFibonacci(2584);
    //setup game
    const unsigned int size = 5;
    const unsigned int min = 0;
    const unsigned int max = 5;
    //game
    sapperGame(size, min, max);
}


void printFibonacci(const unsigned int until) {
    static unsigned int prev = 0;
    static unsigned int prevPrev = 1;

    prev = prev + prevPrev;
    prevPrev = prev - prevPrev;

    if (prev < until) {
        printf("%d ", prev);
        printFibonacci(until);
    } else {
        printf("%d\n", prev);
        prev = 0;
        prevPrev = 1;
    }
}


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

void sapperGame(const unsigned int size, const unsigned int min, const unsigned int max) {
    unsigned int **field = generateField(size, min, max);
    unsigned int **opened = generateField(size, 0, 0);
    unsigned int openedCount = 0; //cached array sum
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            opened[i][j] = 0;

    printf("Welcome to sapper game!\nTry guess all integers in field.\nValues can be between %d and %d\n", min, max);
    while (openedCount != size * size) {
        printField(field, opened, size);
        char buffer[20];
        int choice = 0;
        fgets(buffer, 20, stdin);
        while (!sscanf(buffer, "%d", &choice)) {
            printf("Wrong type. Enter a valid integer\n");
            fgets(buffer, 20, stdin);
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
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
    printField(field, opened, size);
    printf("Game over!\n");
    for (int i = 0; i < size; i++) {
        free(field[i]);
        free(opened[i]);
    }
    free(field);
    free(opened);
}
