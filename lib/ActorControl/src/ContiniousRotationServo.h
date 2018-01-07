#ifndef __CONTINUOUS_ROTATION_SERVO_H__
#define __CONTINUOUS_ROTATION_SERVO_H__

// #include "/home/user/Programme/arduino-1.8.2/hardware/arduino/avr/cores/arduino/Arduino.h"
// #include "/home/user/Programme/arduino-1.8.2/libraries/Servo/src/Servo.h"

#include <Arduino.h>
#include <Servo.h>

typedef enum {
    Backward, Forward
} direction_t;

class ContinuousRotationServo: Servo {
public:
    ContinuousRotationServo(uint8_t port);
    void setSpeed(int percent);
    void setDirection(direction_t dir);
private:
    Servo servo;
    direction_t dir;
    uint8_t speed;
};

#endif
