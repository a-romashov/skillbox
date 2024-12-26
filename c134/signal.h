#ifndef SKILLBOX_SIGNAL_H
#define SKILLBOX_SIGNAL_H

#include <stdint.h>

#define SIGNAL_MULTIPLIER 10
#define SIGNAL_PRECISION_M 2
#define SIGNAL_PRECISION_H 4
#define SIGNAL_PRECISION_V 3
#define FIELD_SIZE_X 110
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
    uint32_t size;
    uint32_t height;
} signal_t;

signal_t *getSignal(uint32_t size, uint32_t noisePercent);

void paintSignal(const signal_t *signal);

void freeSignal(signal_t *signal);

#endif //SKILLBOX_SIGNAL_H
