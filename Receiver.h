#ifndef RECEIVER_H
#define RECEIVER_H

static const size_t NUM_CHANNELS = 4;

class Receiver {
    private:
        uint8_t throttlePin;
        uint8_t rollPin;
        uint8_t pitchPin;
        uint8_t yawPin;

        volatile uint16_t receiverInShared[NUM_CHANNELS] = { 0 };

        volatile uint64_t receiverPulseStartTime[NUM_CHANNELS] = { 0 };

    public:
        Receiver(uint8_t throttle_pin, uint8_t roll_pin,
                 uint8_t pitch_pin,    uint8_t yaw_pin);

        void update(uint16_t channels[NUM_CHANNELS]);
        bool hasSignal();

        friend void updateThrottle();
        friend void updateRoll();
        friend void updatePitch();
        friend void updateYaw();
};

#endif // RECEIVER_H

