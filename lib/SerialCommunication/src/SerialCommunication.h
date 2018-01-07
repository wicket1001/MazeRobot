#ifndef __SERIAL_COMMUNICATION_H__
#define __SERIAL_COMMUNICATION_h__

#include <Arduino.h>
#include <Wire.h>

class SerialCommunication {
public:
    SerialCommunication();
    boolean isEmpty();
    void read(char* buffer);
    void write(char* buffer);
private:

};

#endif
