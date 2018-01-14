#ifndef PPMRECEIVER_H
#define PPMRECEIVER_H

#include <PulsePosition.h>

#include "Receiver.h"

class PPMReceiver : Receiver {
    private:
        uint8_t inputPin;
        PulsePositionInput inputPpm;
        int count = 0;

    public:
        PPMReceiver(uint8_t _inputPin);
        
        const void update(channels_t channels);
        const bool hasSignal();
};

#endif // PPMRECEIVER_H
