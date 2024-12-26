#include "stdlib.h"
#include "signal.h"
#include "math.h"
#include "stdio.h"

double getNoise(const uint32_t noisePercent) {
    return ((rand() % 2 == 0 ? 0 : 1) * rand() % SIGNAL_MULTIPLIER) / 100.0 * noisePercent;
}

double getSignalValue(const double alpha, uint32_t noisePercent) {
    double precision = pow(SIGNAL_PRECISION_M, SIGNAL_PRECISION_V);
    return floor(
            (
                    SIGNAL_MULTIPLIER * sin(M_PI_2 * alpha / SIGNAL_PRECISION_M) + getNoise(noisePercent)
            ) * precision
    ) / precision;
}

uint32_t getFieldIndex(
        const uint16_t size,
        const uint16_t zeroIndex,
        const double value,
        const uint32_t signalSize
) {
    if (value == 0) {
        return zeroIndex;
    }
    uint32_t result;
    if (value < 0) {
        result = zeroIndex - (uint32_t) floor((zeroIndex / (double) (signalSize)) * value * -1);
    } else {
        int newSize = size - zeroIndex;
        result = zeroIndex + (uint32_t) floor((newSize / (double) (signalSize)) * value);
    }

    return result;
}

char **getField(
        const signal_t *signal,
        const uint32_t sizeX,
        const uint32_t sizeY,
        const uint32_t zeroX,
        const uint32_t zeroY
) {
    char **field = malloc(sizeof(char *) * sizeY);

    for (int i = 0; i < sizeY; i++) {
        field[sizeY - 1 - i] = malloc(sizeof(char) * sizeX);
        for (int j = 0; j < sizeX; j++) {

            if (i == getFieldIndex(sizeY, zeroY, 0, signal->size) &&
                j == getFieldIndex(sizeX, zeroX, 0, signal->size)) {
                field[sizeY - 1 - i][j] = '+';
            } else if (i == getFieldIndex(sizeY, zeroY, 0, signal->size)) {
                field[sizeY - 1 - i][j] = '-';
            } else if (j == getFieldIndex(sizeX, zeroX, 0, signal->size)) {
                field[sizeY - i - 1][j] = '|';
            } else {
                field[sizeY - i - 1][j] = ' ';
            }
        }
    }
    return field;
}

void freeField(char **field, uint32_t size) {
    for (int i = 0; i < size; i++) {
        free(field[i]);
    }
    free(field);
}

void printField(char **field, uint32_t sizeX, uint32_t sizeY) {
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            printf("%c", field[i][j]);
        }
        printf("\n");
    }
}

void fillFieldBySignal(
        char **field,
        const signal_t *signal,
        const uint32_t sizeX,
        const uint32_t sizeY,
        const uint32_t zeroX,
        const uint32_t zeroY
) {

    for (int i = 0; i < signal->size; i++) {

        uint32_t x = getFieldIndex(
                sizeX,
                zeroX,
                signal->points[i]->x,
                signal->size / (uint32_t) pow(SIGNAL_PRECISION_M, SIGNAL_PRECISION_H)
        );

        uint32_t y = getFieldIndex(
                sizeY - 1,
                zeroY,
                signal->points[i]->y,
                signal->height
        );

        field[sizeY - 1 - y][x] = FIELD_CHAR;
    }
}

double getSumPeriod(signal_t *signal, uint32_t period, uint32_t index) {
    double result = 0;
    uint32_t half = period / 2;
    uint32_t startAddon = index < half ? half - index : 0;
    uint32_t endAddon = index + half > signal->size ? index + half - signal->size : 0;

    uint32_t start = index - (half - startAddon);
    uint32_t stop = index + (half - endAddon);

    for (uint32_t i = start; i < stop; i++) {
        result += signal->points[i]->y;
    }
    /**
     * Компенсация
     */
    result += signal->points[index]->y * (startAddon + endAddon);

    return result / period;
}


signal_t *getSignal(uint32_t size, uint32_t noisePercent) {

    signal_t *signal = malloc(sizeof(signal_t));

    signal->size = size * (int) pow(SIGNAL_PRECISION_M, SIGNAL_PRECISION_H);
    signal->points = malloc(sizeof(point_t *) * signal->size);
    signal->height = SIGNAL_MULTIPLIER + SIGNAL_MULTIPLIER * noisePercent / 100;

    for (int i = 0; i < signal->size; i++) {

        point_t *point = malloc(sizeof(point_t));

        point->x = i / (double) pow(SIGNAL_PRECISION_M, SIGNAL_PRECISION_H);
        point->y = getSignalValue(point->x, noisePercent);

        signal->points[i] = point;
    }

    return signal;
}

void paintSignal(const signal_t *signal) {
    printf("\n\n");

    uint32_t sizeX = FIELD_SIZE_X;
    uint32_t sizeY = FIELD_SIZE_Y;
    uint32_t zeroX = FIELD_MIDDLE_X;
    uint32_t zeroY = FIELD_MIDDLE_Y;

    char **field = getField(signal, sizeX, sizeY, zeroX, zeroY);

    fillFieldBySignal(field, signal, sizeX, sizeY, zeroX, zeroY);

    printField(field, sizeX, sizeY);

    freeField(field, sizeY);

    printf("\n\n");
}

void freeSignal(signal_t *signal) {

    for (int i = 0; i < signal->size; i++) {
        free(signal->points[i]);
    }
    free(signal->points);
    free(signal);
}

signal_t *filterSignal(signal_t *signal, uint32_t period) {

    signal_t *result = malloc(sizeof(signal_t));
    result->points = malloc(sizeof(point_t *) * signal->size);
    result->size = signal->size;
    result->height = signal->height;

    for (int i = 0; i < signal->size; i++) {
        result->points[i] = malloc(sizeof(point_t));
        result->points[i]->x = signal->points[i]->x;
        result->points[i]->y = signal->points[i]->y;
    }

    for (int i = 0; i < signal->size; i++) {
        if (i) {
            result->points[i]->y = getSumPeriod(signal, period, i);
        }
    }

    return result;
}