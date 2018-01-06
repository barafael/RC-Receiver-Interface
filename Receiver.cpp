#include "Arduino.h"
#include "WProgram.h"

#include "Receiver.h"

/* Access variable for ISRs */
static Receiver *instance = NULL;

typedef enum {
    THROTTLE_CHANNEL = 0,
    AILERON_CHANNEL  = 1,
    ELEVATOR_CHANNEL = 2,
    RUDDER_CHANNEL   = 3
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

void updateAileron() {
    if (digitalRead(instance->aileronPin) == HIGH) {
        instance->receiverPulseStartTime[AILERON_CHANNEL] = micros();
    } else {
        instance->receiverInShared[AILERON_CHANNEL] =
            (uint16_t)(micros() - instance->receiverPulseStartTime[AILERON_CHANNEL]);
    }
}

void updateElevator() {
    if (digitalRead(instance->elevatorPin) == HIGH) {
        instance->receiverPulseStartTime[ELEVATOR_CHANNEL] = micros();
    } else {
        instance->receiverInShared[ELEVATOR_CHANNEL] =
            (uint16_t)(micros() - instance->receiverPulseStartTime[ELEVATOR_CHANNEL]);
    }
}

void updateRudder() {
    if (digitalRead(instance->rudderPin) == HIGH) {
        instance->receiverPulseStartTime[RUDDER_CHANNEL] = micros();
    } else {
        instance->receiverInShared[RUDDER_CHANNEL] =
            (uint16_t)(micros() - instance->receiverPulseStartTime[RUDDER_CHANNEL]);
    }
}

Receiver::Receiver(uint8_t _throttlePin, uint8_t _aileronPin,
                   uint8_t _elevatorPin, uint8_t _rudderPin) {
    throttlePin = _throttlePin;
    aileronPin     = _aileronPin;
    elevatorPin    = _elevatorPin;
    rudderPin      = _rudderPin;

    /* The pinMode should be set to input by default, set it anyway */
    pinMode(throttlePin, INPUT);
    pinMode(aileronPin,  INPUT);
    pinMode(elevatorPin, INPUT);
    pinMode(rudderPin,   INPUT);

    /* On each CHANGE on an input pin, an interrupt handler is called */
    attachInterrupt(throttlePin, updateThrottle, CHANGE);
    attachInterrupt(aileronPin,  updateAileron,  CHANGE);
    attachInterrupt(elevatorPin, updateElevator, CHANGE);
    attachInterrupt(rudderPin,   updateRudder,   CHANGE);

    instance = this;

    /* TODO Check if delay necessary for has_signal */
    delay(10);
}

void Receiver::printChannels() {
    Serial.print(getThrottle());
    Serial.print('\t');
    Serial.print(getAileron());
    Serial.print('\t');
    Serial.print(getElevator());
    Serial.print('\t');
    Serial.println(getRudder());
}

uint32_t Receiver::getThrottle() {
    return receiverIn[THROTTLE_CHANNEL];
}

uint32_t Receiver::getAileron() {
    return receiverIn[AILERON_CHANNEL];
}

uint32_t Receiver::getElevator() {
    return receiverIn[ELEVATOR_CHANNEL];
}

uint32_t Receiver::getRudder() {
    return receiverIn[RUDDER_CHANNEL];
}

/*
   —————————————————————————————————————————————————————————
   ———             RECEIVER UPDATE FUNCTION              ———
   —————————————————————————————————————————————————————————
*/

void Receiver::update() {
    noInterrupts();
    for (size_t index = 0; index < 4; index++) {
        receiverIn[index] = receiverInShared[index];
    }
    interrupts();

    for (size_t index = 0; index < 4; index++) {
        if (receiverIn[index] < 1000) receiverIn[index] = 1000;
        if (receiverIn[index] > 2000) receiverIn[index] = 2000;
    }
}

bool Receiver::hasSignal() {
    this->update();
    for (size_t index = 0; index < 4; index++) {
        if (receiverIn[index] == 0) {
            return false;
        }
    }
    return true;
}

