#include "WS2812B.h"

WS2812B::WS2812B(uint8_t portRed, uint8_t portGreen, uint8_t portBlue) {
    this->portRed = portRed;
    this->portGreen = portGreen;
    this->portBlue = portBlue;
}

void WS2812B::setColor(uint16_t color) {
    uint8_t hi = color / 60;
    float f = color / 60.0 - hi;
    float q = 1 - f;
    switch (hi) {
        case 0:
            setRGB(255, f, 0);
            break;
        case 1:
            setRGB(q, 255, 0);
            break;
        case 2:
            setRGB(0, 255, f);
            break;
        case 3:
            setRGB(0, q, 255);
            break;
        case 4:
            setRGB(f, 0, 255);
            break;
        case 5:
            setRGB(255, 0, q);
            break;
        default:
            break;
    }
}

void WS2812B::setRGB(uint8_t red, uint8_t green, uint8_t blue) {
    analogWrite(portRed, red);
    analogWrite(portGreen, green);
    analogWrite(portBlue, blue);
}
