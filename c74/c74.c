//
// Created by Андрей on 19.10.2024.
//
#include <stdio.h>

void task1() {
    printf("Enter 5 integers to find average\n");
    int numbers[5];
    int avg = 0;
    for (int i = 0; i < 5; i++) {
        char buf[50];
        printf("enter integer #%d:", i + 1);
        fgets(buf, 50, stdin);
        int val = 0;
        while (!sscanf(buf, "%d", &val)) {
            printf("can`t read an integer, try to type again\n");
            fgets(buf, 50, stdin);
        };
        numbers[i] = val;
        avg+= val;
    }
    //зачем заполнял массив хз
    printf("average of integers is %.2f\n", (float)avg / 5.0f);
}
void task2() {
    printf("Enter 10 integers to find max\n");
    int numbers[10];
    int maxI = 0;
    for (int i = 0; i < 10; i++) {
        char buf[50];
        printf("enter integer #%d:", i + 1);
        fgets(buf, 50, stdin);

        while (!sscanf(buf, "%d", &numbers[i])) {
            printf("can`t read an integer, try to type again\n");
            fgets(buf, 50, stdin);
        };

        if (numbers[maxI] < numbers[i]) {
            maxI = i;
        }
    }

    printf("the biggest value is %d with index %d\n", numbers[maxI], maxI);
}
void task3() {
    float array2d[4][5];
    for (int i = 0; i < 4; i++) {
        char buf[50];
        printf("Enter 5 float numbers separated with space #%d:", i + 1);
        fgets(buf, 50, stdin);
        int val = 0;
        while (5 != sscanf(
            buf,
            "%f %f %f %f %f",
            &array2d[i][0],
            &array2d[i][1],
            &array2d[i][2],
            &array2d[i][3],
            &array2d[i][4]
        )) {
            printf("can`t read 5 floats, try to type again\n");
            fgets(buf, 50, stdin);
        };
    }
    float result[4];
    for(int i = 0; i < 4; i++) {
        result[i] = array2d[i][0];
        int findMax = result[i] >= 0;
        for (int j = 0; j < 5; j++) {
            if (findMax) {
                result[i] = result[i] < array2d[i][j] ? array2d[i][j] : result[i];
            } else {
                result[i] = result[i] > array2d[i][j] ? array2d[i][j] : result[i];
            }
        }
        printf(findMax ? "max" : "min");
        printf(" value in data with index %d is %.2f\n", i, result[i]);
    }
}
void task4() {
    int x[10];
    int y[10];

    printf("Enter 10 integers for X\n");
    for (int i = 0; i < 10; i++) {
        char buf[50];
        printf("enter integer #%d:", i + 1);
        fgets(buf, 50, stdin);
        int val = 0;
        while (!sscanf(buf, "%d", &val)) {
            printf("can`t read an integer, try to type again\n");
            fgets(buf, 50, stdin);
        };
        x[i] = val;
    }
    printf("Enter 10 integers for Y\n");
    for (int i = 0; i < 10; i++) {
        char buf[50];
        printf("enter integer #%d:", i + 1);
        fgets(buf, 50, stdin);
        int val = 0;
        while (!sscanf(buf, "%d", &val)) {
            printf("can`t read an integer, try to type again\n");
            fgets(buf, 50, stdin);
        };
        y[i] = val;
    }

    int xAsc = 1;
    int yAsc = 1;
    printf("X initial data is");
    for (int i = 0; i < 10; i++) {
        printf(" %d", x[i]);
        if (i && x[i-1] > x[i]) {
            xAsc = 0;
        }
    }
    printf("\n");
    printf("Y initial data is");
    for (int i = 0; i < 10; i++) {
        printf(" %d", y[i]);
        if (i && y[i-1] > y[i]) {
            yAsc = 0;
        }
    }
    printf("\n");
    printf("X current data is");
    for (int i = 0; i < 10; i++) {
        x[i] = xAsc && x[i] > 0 ? 0 : x[i];
        printf(" %d", x[i]);
    }
    printf("\n");
    printf("Y current data is");
    for (int i = 0; i < 10; i++) {
        y[i] = yAsc && y[i] > 0 ? 0 : y[i];
        printf(" %d", y[i]);
    }
    printf("\n");
}

void main() {
    task1();
    task2();
    task3();
    task4();
}