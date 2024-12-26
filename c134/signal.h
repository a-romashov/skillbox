#ifndef SKILLBOX_SIGNAL_H
#define SKILLBOX_SIGNAL_H

#include <stdint.h>

#define SIGNAL_MULTIPLIER 20
#define SIGNAL_PRECISION_M 2
#define SIGNAL_PRECISION_H 3
#define SIGNAL_PRECISION_V 2
#define FIELD_SIZE_X 110
#define FIELD_SIZE_Y 30
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

signal_t *filterSignal(signal_t *signal, uint32_t period);

#endif //SKILLBOX_SIGNAL_H
