#include "Receiver.h"

Receiver receiver(8, 9, 10, 11);

void setup() {
    Serial.begin(9600);
}

void loop() {
    receiver.update();
    receiver.printChannels();
    delay(5);
}

