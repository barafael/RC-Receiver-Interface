#ifndef RECEIVER_H
#define RECEIVER_H

class Receiver {
private:
    uint8_t throttlePin;
    uint8_t aileronPin;
    uint8_t elevatorPin;
    uint8_t rudderPin;

    volatile uint16_t receiverInShared[4] = { 0 };

    volatile uint16_t receiverIn[4] = { 0 };

    volatile uint64_t receiverPulseStartTime[4] = { 0 };

public:
    Receiver(uint8_t throttle_pin, uint8_t aileron_pin,
             uint8_t elevator_pin, uint8_t rudder_pin);

    void update();
    bool hasSignal();
    void getChannels(uint16_t channels[4]);

    uint16_t getThrottle();
    uint16_t getAileron();
    uint16_t getElevator();
    uint16_t getRudder();

    friend void updateThrottle();
    friend void updateAileron();
    friend void updateElevator();
    friend void updateRudder();
};

#endif // RECEIVER_H

