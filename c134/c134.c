#include "stdio.h"
#include "../lib/SafeInput/SafeInput.h"
#include "signal.h"

int main() {

    printf("Enter size of signal: \n");
    int size;
    scanInteger("%d", &size, "try enter int again\n");

    signal_t* signal = getSignal(size, 40);
    paintSignal(signal);
    freeSignal(signal);
}

