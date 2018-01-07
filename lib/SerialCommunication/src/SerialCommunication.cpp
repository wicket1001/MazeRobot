#include "SerialCommunication.h"

SerialCommunication::SerialCommunication() {
    Serial.begin(9600);
    Serial.println("H");
}

boolean SerialCommunication::isEmpty() {
    return !Serial.available();
}

void SerialCommunication::read(char* buffer) {
    int index = 0;
    while(!isEmpty()) {
        buffer[index] = Serial.read();
        index ++;
        delay(10);
    }
}

void SerialCommunication::write(char* buffer) {
    Serial.print("Output: ");
    Serial.println(buffer);
}
