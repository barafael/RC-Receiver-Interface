#ifndef RECEIVER_H
#define RECEIVER_H

static const size_t NUM_CHANNELS = 4;

class Receiver {
    public:
        using channels_t = uint16_t[NUM_CHANNELS];
        virtual const void update(uint16_t channels[NUM_CHANNELS]);
        virtual const bool has_signal();
};

#endif // RECEIVER_H
