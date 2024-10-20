#include <stdio.h>

void task1() {
    float var = 33.3f;
    float *pVar = &var;
    printf("variable address is %p, value is %.1f\n", (void *) pVar, *pVar);
    *pVar = 77.7f;
    printf("variable address is %p, value is %.1f\n", (void *) pVar, *pVar);
}

void task2() {
    int array[5] = {5, 11, 33, -5, 0};

    for (int i = 0; i < 5; i++)
        printf(i ? " %d" : "%d", *(array + i));
    printf("\n");

    for (int i = 0; i < 5; i++) {
        for (int j = i; j < 5; j++) {
            if (*(array + i) > *(array + j)) {
                int tmp = *(array + i);
                *(array + i) = *(array + j);
                *(array + j) = tmp;
            }
        }
    }

    for (int i = 0; i < 5; i++)
        printf(i ? " %d" : "%d", *(array + i));
    printf("\n");
}

void task3() {
    int array[5] = {15, 22, 55, -15, 10};

    for (int i = 0; i < 5; i++)
        printf(i ? " %d" : "%d", *(array + i));
    printf("\n");

    int sum = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = i; j < 5; j++) {
            if (*(array + i) > *(array + j)) {
                int tmp = *(array + i);
                *(array + i) = *(array + j);
                *(array + j) = tmp;
            }
        }
        sum += *(array + i);
    }

    printf(
        "avg = %.2f; med = %d; min = %d; max = %d\n",
        (float) sum / 5,
        *(array + 2),
        *array,
        *(array + 4)
    );
}


void main() {
    printf("-----\n");
    task1();
    printf("-----\n");
    task2();
    printf("-----\n");
    task3();
}
