#ifndef PWM_RECEIVER_H
#define PWM_RECEIVER_H

#include "Receiver.h"

class PWMReceiver : Receiver {
    private:
        uint8_t throttlePin;
        uint8_t rollPin;
        uint8_t pitchPin;
        uint8_t yawPin;

        volatile uint16_t receiverInShared[NUM_CHANNELS] = { 0 };

        volatile uint64_t receiverPulseStartTime[NUM_CHANNELS] = { 0 };

    public:
        PWMReceiver(uint8_t throttlePin, uint8_t rollPin,
                    uint8_t pitchPin,    uint8_t yawPin);

        void const update(uint16_t channels[NUM_CHANNELS]);
        bool const hasSignal();

        friend void updateThrottle();
        friend void updateRoll();
        friend void updatePitch();
        friend void updateYaw();
};

#endif // PWM_RECEIVER_H

