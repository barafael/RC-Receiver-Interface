#include "Arduino.h"
#include "WProgram.h"

#include "../include/Receiver.h"

#include "../include/PWM_Receiver.h"

/* Access variable for ISRs */
static PWMReceiver *instance = nullptr;

typedef enum {
    THROTTLE_CHANNEL = 0,
    ROLL_CHANNEL     = 1,
    PITCH_CHANNEL    = 2,
    YAW_CHANNEL      = 3
} input_channel;

/*
   ————————————————————————————————————————————————————————————————
   ———             RECEIVER READ INTERRUPT ROUTINES             ———
   ————————————————————————————————————————————————————————————————
*/

void updateThrottle() {
    if (digitalRead(instance->throttlePin) == HIGH) {
        instance->receiverPulseStartTime[THROTTLE_CHANNEL] = micros();
    } else {
        instance->receiverInShared[THROTTLE_CHANNEL] =
            (uint16_t)(micros() - instance->receiverPulseStartTime[THROTTLE_CHANNEL]);
    }
}

void updateRoll() {
    if (digitalRead(instance->rollPin) == HIGH) {
        instance->receiverPulseStartTime[ROLL_CHANNEL] = micros();
    } else {
        instance->receiverInShared[ROLL_CHANNEL] =
            (uint16_t)(micros() - instance->receiverPulseStartTime[ROLL_CHANNEL]);
    }
}

void updatePitch() {
    if (digitalRead(instance->pitchPin) == HIGH) {
        instance->receiverPulseStartTime[PITCH_CHANNEL] = micros();
    } else {
        instance->receiverInShared[PITCH_CHANNEL] =
            (uint16_t)(micros() - instance->receiverPulseStartTime[PITCH_CHANNEL]);
    }
}

void updateYaw() {
    if (digitalRead(instance->yawPin) == HIGH) {
        instance->receiverPulseStartTime[YAW_CHANNEL] = micros();
    } else {
        instance->receiverInShared[YAW_CHANNEL] =
            (uint16_t)(micros() - instance->receiverPulseStartTime[YAW_CHANNEL]);
    }
}

PWMReceiver::PWMReceiver(uint8_t _throttlePin, uint8_t _rollPin,
                         uint8_t _pitchPin,    uint8_t _yawPin) {

    throttlePin = _throttlePin;
    rollPin     = _rollPin;
    pitchPin    = _pitchPin;
    yawPin      = _yawPin;

    /* The pinMode should be set to input by default, set it anyway */
    pinMode(throttlePin, INPUT);
    pinMode(rollPin,     INPUT);
    pinMode(pitchPin,    INPUT);
    pinMode(yawPin,      INPUT);

    /* On each CHANGE on an input pin, an interrupt handler is called */
    attachInterrupt(throttlePin, updateThrottle, CHANGE);
    attachInterrupt(rollPin,     updateRoll,     CHANGE);
    attachInterrupt(pitchPin,    updatePitch,    CHANGE);
    attachInterrupt(yawPin,      updateYaw,      CHANGE);

    instance = this;

    /* TODO Check if delay necessary for hasSignal */
    delay(10);
}


/*
   —————————————————————————————————————————————————————————
   ———             RECEIVER UPDATE FUNCTION              ———
   —————————————————————————————————————————————————————————
*/

void const PWMReceiver::update(uint16_t channels[NUM_CHANNELS]) {
    noInterrupts();
    for (size_t index = 0; index < NUM_CHANNELS; index++) {
        channels[index] = receiverInShared[index];
    }
    interrupts();

    for (size_t index = 0; index < NUM_CHANNELS; index++) {
        if (channels[index] < 1000) channels[index] = 1000;
        if (channels[index] > 2000) channels[index] = 2000;
        channels[index] -= 1000;
    }
}

bool const PWMReceiver::hasSignal() {
    noInterrupts();
    for (size_t index = 0; index < NUM_CHANNELS; index++) {
        if (receiverInShared[index] == 0) {
            interrupts();
            return false;
        }
    }
    interrupts();
    return true;
}

