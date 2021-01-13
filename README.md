# RC-Receiver-Interface - A library for reading RC receivers

Disclaimer: You should probably do this with Timers and/or DMA,
but for a quick solution this works fine...

This library provides a ```Receiver``` object from which you can read the input
from an RC receiver. There are many sketches around the internet which achieve
the same result, but some of them use blocking functions (i.e. pulseIn()) or
are just long C files. This library provides an object-oriented receiver
interface.  As input, PWM and CPPM signals are supported. For the latter, only
one pin is needed, but it uses the teensy-specific PulsePosition library.

# Supported Devices

This library works fine on the Teensy 3.2 and Teensy LC. Please
[let me know](rafael.bachmann.93@gmail.com) if you got it working on a
different board and feel free to open a PR.

The Arduino Uno is NOT supported for reading 4 channels because it only has 2
pins that can handle interrupts. You can easily  adapt the library to just use
2 channels.

# Notes on Interrupts

Please ensure that the pins you give the Receiver constructor are
interrupt-capable. On the Teensy 3.2, all digital pins can be used.

If your program disables interrupts for long stretches of time, then you will
probably notice inaccuracies from this library, since it relies on interrupts
for detecting receiver signals.

# Example Sketch and Hardware Setup

The example sketch ```RC-Receiver-Interface.ino``` sets up the receiver such
that you can connect your receiver to pins 8, 9, 10, 11. Channel order is
throttle, aileron, elevator, rudder.  Make sure you choose the right signal
type (ppm, pwm) in the code and your receiver.
