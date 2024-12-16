#include "stdio.h"
#include "stdlib.h"
#include "../lib/SafeInput/SafeInput.h"
#include "math.h"


#define NOISE_PERCENT 20
#define SIGNAL_MULTIPLIER 10
#define SIGNAL_PRECISION_H 1
#define SIGNAL_PRECISION_V 1

#define FIELD_SIZE_X 111
#define FIELD_SIZE_Y 27
#define FIELD_MIDDLE_X 5
#define FIELD_MIDDLE_Y {(FIELD_SIZE_Y - 1) / 2}
#define FIELD_CHAR 'X';

typedef struct {
    double x;
    double y;
} point_t;

typedef struct {
    point_t **points;
    unsigned int size;
} signal_t;

double getSignalValue(double alpha);
void paintSignal(const signal_t *signal);

int main() {

    printf("Enter size of signal: \n");
    int size;
    scanInteger("%d", &size, "try enter int again\n");

    signal_t signal;
    signal.size = size * (int)pow(10, SIGNAL_PRECISION_H);
    signal.points = malloc(sizeof(point_t *) * signal.size);
    for (int i = 0; i < signal.size; i++) {
        point_t *point = malloc(sizeof(point_t));
        point->x = i / (double)pow(10, SIGNAL_PRECISION_H);
        point->y = getSignalValue(point->x);
        signal.points[i] = point;
    }

    paintSignal(&signal);

    for (int i = 0; i < signal.size; i++) {
        free(signal.points[i]);
    }
    free(signal.points);
}

double getNoise() {
    return (rand() % SIGNAL_MULTIPLIER) / 100.0 * NOISE_PERCENT;
}

double getSignalValue(const double alpha) {
    double precision = pow(10, SIGNAL_PRECISION_V);
    return floor((SIGNAL_MULTIPLIER * sin(alpha) + getNoise()) * precision) / precision;
}

void printField(char **field, unsigned int sizeX, unsigned int sizeY) {
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            printf("%c", field[i][j]);
        }
        printf("\n");
    }
}

unsigned int getFieldIndex(unsigned short int size, unsigned short int zeroIndex, double value, unsigned int signalSize) {
    if (value == 0) {
        return zeroIndex;
    }
    unsigned int result;
    if (value < 0) {
        result = zeroIndex - (unsigned int) floor((zeroIndex / (double)signalSize) * value * -1);
    } else {
        int newSize = size - zeroIndex;
        result = zeroIndex + (unsigned int) floor((newSize / (double)signalSize) * value);
    }

    return result < 1 ? 1 : result > size ? size : result;
}

void paintSignal(const signal_t *signal) {
    printf("\n\n");
    unsigned int sizeX = FIELD_SIZE_X;
    unsigned int sizeY = FIELD_SIZE_Y;
    unsigned int zeroX = FIELD_MIDDLE_X;
    unsigned int zeroY = FIELD_MIDDLE_Y;

    char ** field = malloc(sizeof(char*) * sizeY);
    for (int i = 0; i < sizeY; i++) {
        field[sizeY - 1 - i] = malloc(sizeof(char) * sizeX);
        for (int j = 0; j < sizeX; j++) {

            if (i == getFieldIndex(sizeY, zeroY, 0, signal->size) && j == getFieldIndex(sizeX, zeroX, 0, signal->size)) {
                field[sizeY- 1 - i][j] = '+';
            } else if (i == getFieldIndex(sizeY, zeroY, 0, signal->size)) {
                field[sizeY - 1 - i][j] = '-';
            } else if (j == getFieldIndex(sizeX, zeroX, 0, signal->size)) {
                field[sizeY - i - 1][j] = '|';
            } else {
                field[sizeY - i - 1][j] = ' ';
            }
        }
    }


    for (int i = 0; i < signal->size; i++) {
        unsigned int x = getFieldIndex(sizeX, zeroX, signal->points[i]->x, signal->size / (unsigned int)pow(10, SIGNAL_PRECISION_H));
        unsigned int y = getFieldIndex(sizeY, zeroY, signal->points[i]->y, SIGNAL_MULTIPLIER + SIGNAL_MULTIPLIER * NOISE_PERCENT / 100);

        field[sizeY - y - 1][x] = FIELD_CHAR;
    }

    printField(field, sizeX, sizeY);
    for (int i = 0; i < sizeY; i++) {
        free(field[i]);
    }
    free(field);

    printf("\n\n");
}
