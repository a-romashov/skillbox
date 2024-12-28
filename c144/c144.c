#include "stdio.h"
#include "../c134/signal.h"

#define SIZE 20
#define NOISE 20
#define FILTER 10

int main() {

    signal_t *signalClean = getSignal(SIZE, 0);

    printf("Clean signal\n");
    paintSignal(signalClean);
    freeSignal(signalClean);

    signal_t *signalNoised = getSignal(SIZE, NOISE);
    printf("Noised signal\n");
    paintSignal(signalNoised);

    signal_t *signalFiltered = filterSignal(signalNoised, FILTER);
    freeSignal(signalNoised);

    printf("Filtered signal\n");
    paintSignal(signalFiltered);
    freeSignal(signalFiltered);

    return 0;
}