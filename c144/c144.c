#include "stdio.h"
#include "../c134/signal.h"

#define SIZE 20
#define NOISE 20
#define FILTER 10

int main() {

    signal_t *signalClean = getSignal(SIZE, 0);
    signal_t *signalNoised = getSignal(SIZE, NOISE);
    signal_t *signalFiltered = filterSignal(signalNoised, FILTER);

    printf("Clean signal\n");
    paintSignal(signalClean);
    printf("Noised signal\n");
    paintSignal(signalNoised);
    printf("Filtered signal\n");
    paintSignal(signalFiltered);

    return 0;
}