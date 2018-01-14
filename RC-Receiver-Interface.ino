#include "./include/PPM_Receiver.h"
#include "./include/Receiver.h"

Receiver receiver(19, 20, 21, 22);
PPMReceiver pwm_receiver(10);

#define use_ppm

uint16_t channels[4] = { 0 };

void setup() {
    Serial.begin(9600);
}

void loop() {
#ifdef use_pwm
    receiver.update(channels);
    for (int index = 0; index < 4; index++) {
        Serial.print(channels[index]);
        Serial.print("\t");
    }
    Serial.println();
    delay(5);
#endif

#ifdef use_ppm

    pwm_receiver.update(channels);
    for (int index = 0; index < 8; index++) {
        Serial.print(channels[index]);
        Serial.print("\t");
    }
    Serial.println();
    delay(5);

#endif
}
