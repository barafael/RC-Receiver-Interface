#ifndef RECEIVER_H
#define RECEIVER_H

class Receiver {
    private:
        uint8_t throttlePin;
        uint8_t rollPin;
        uint8_t pitchPin;
        uint8_t yawPin;

        volatile uint16_t receiverInShared[4] = { 0 };

        volatile uint64_t receiverPulseStartTime[4] = { 0 };

    public:
        Receiver(uint8_t throttle_pin, uint8_t roll_pin,
                 uint8_t pitch_pin,    uint8_t yaw_pin);

        void update(uint16_t channels[4]);
        bool hasSignal();

        friend void updateThrottle();
        friend void updateRoll();
        friend void updatePitch();
        friend void updateYaw();
};

#endif // RECEIVER_H

