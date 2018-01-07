#ifndef __WS2812B_H__
#define __WS2812B_H__

#include "/home/user/Programme/arduino-1.8.2/hardware/arduino/avr/cores/arduino/Arduino.h"

class WS2812B {
public:
    WS2812B(uint8_t portRed, uint8_t portGreen, uint8_t portBlue);
    void setColor(uint16_t color);
    void setRGB(uint8_t red, uint8_t green, uint8_t blue);
private:
    uint8_t portRed;
    uint8_t portGreen;
    uint8_t portBlue;
};

#endif
