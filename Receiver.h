#ifndef RECEIVER_H
#define RECEIVER_H

class Receiver {
    private:
        uint32_t throttlePin;
        uint32_t aileronPin;
        uint32_t elevatorPin;
        uint32_t rudderPin;

        volatile uint32_t receiverInShared[4] = { 0 };

        volatile uint32_t receiverIn[4] = { 0 };

        volatile uint64_t receiverPulseStartTime[4] = { 0 };

    public:
        Receiver(uint8_t throttle_pin, uint8_t aileron_pin,
                 uint8_t elevator_pin, uint8_t rudder_pin);

        void update();
        bool hasSignal();
        void printChannels();

        uint32_t getThrottle();
        uint32_t getAileron();
        uint32_t getElevator();
        uint32_t getRudder();

        friend void updateThrottle();
        friend void updateAileron();
        friend void updateElevator();
        friend void updateRudder();
};

#endif // RECEIVER_H

