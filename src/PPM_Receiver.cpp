#include "Arduino.h"
#include "WProgram.h"

#include "../include/PPM_Receiver.h"

PPMReceiver::PPMReceiver(uint8_t _inputPin) {
    
    inputPin = _inputPin;
    inputPpm.begin(inputPin);
    
    delay(10);
}

const void PPMReceiver::update(channels_t channels) {
    int num = inputPpm.available();
    if (num > 0) {
        count = count + 1;
        for (size_t index = 0; index < NUM_CHANNELS; index++) {
            float val = inputPpm.read(index + 1);
            channels[index] = (uint16_t) val;
            if (channels[index] < 1000) channels[index] = 1000;
            if (channels[index] > 2000) channels[index] = 2000;
            channels[index] -= 1000;
        }
    }
}

const bool PPMReceiver::hasSignal() {
    return true;
}
