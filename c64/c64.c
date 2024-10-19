#include <stdio.h>

void printCountdown() {
    short i = 10;
    while (i--) printf("%d\n", i);
}

void printPifagorsTable() {
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            printf("%d ", i * j);
            j < 9 && printf(i * j < 10 ? "  " : " ");
        }
        printf("\n");
    }
}

void getAndSortThenPrint() {
    char buf[10];
    short size = 0;

    do {
        printf("Enter count of numbers between 1 and 10:");
        fgets(buf, 50, stdin);
        sscanf(buf, "%hud", &size);
    } while (size < 1 || size > 10);

    int numbers[size];

    printf("Enter an integers\n");
    for (int i = 0; i < size; i++) {
        printf("enter integer #%d:", i + 1);
        fgets(buf, 50, stdin);
        int val = 0;
        while (!sscanf(buf, "%d", &val)) {
            printf("can`t read an integer, try to type again\n");
            fgets(buf, 50, stdin);
        };
        numbers[i] = val;
    }

    printf("collected numbers:");
    for (int i = 0; i < size; i++) {
        printf(" %d", numbers[i]);
    }
    printf("\nsorted numbers:");
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (numbers[i] > numbers[j]) {
                int tmp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = tmp;
            }
        }
    }
    for (int i = 0; i < size; i++) {
        printf(" %d", numbers[i]);
    }
    printf("\n");
}

int printMenu() {
    int operation = -1;
    printf("Enter operation id:");
    char buf[5];
    fgets(buf, 5, stdin);
    sscanf(buf, "%d", &operation);

    return operation;
}

void main() {
    while (1) {
        switch (printMenu()) {
            case 1: printCountdown();
                break;
            case 2: printPifagorsTable();
                break;
            case 3: getAndSortThenPrint();
                break;
            default:
                printf("wrong command id\n");
                break;
        }
    }
}
