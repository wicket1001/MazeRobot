/**
 * @author Harald Moritz
 * A Serial Communication library.
 */
#include "SerialCommunication.h"

/**
 * The default constructor that begins the Serial communication.
 */
SerialCommunication::SerialCommunication() {
    Serial.begin(9600);
}

/**
 * Return if the Serial cache is empty.
 *
 * @return If the Serial cache is empty.
 */
boolean SerialCommunication::isEmpty() {
    return !Serial.available();
}

/**
 * Reads the Serial cache into the buffer.
 *
 * @param buffer A char buffer to read the Serial cache in.
 */
void SerialCommunication::read(char* buffer) {
    int index = 0;
    while(!isEmpty()) {
        buffer[index] = Serial.read();
        index ++;
        delay(10);
    }
}

/**
 * Writes the buffer to the Serial buffer.
 *
 * @param buffer A char buffer to write to the Serial cache.
 */
void SerialCommunication::write(char* buffer) {
    Serial.println(buffer);
}
