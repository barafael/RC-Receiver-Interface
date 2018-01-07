#include "Receiver.h"

Receiver receiver(8, 9, 10, 11);

uint16_t channels[4] = { 0 };

void setup() {
    Serial.begin(9600);
}

void loop() {
    receiver.update(channels);
    for (int index = 0; index < 4; index++) {
        Serial.print(channels[index]);
        Serial.print("\t");
    }
    Serial.println();
    delay(5);
}

