#ifndef __CONTINUOUS_ROTATION_SERVO_H__
#define __CONTINUOUS_ROTATION_SERVO_H__

#include <Arduino.h>
#include <Servo.h>

typedef enum {
    Backward, Forward
} direction_t;

class ContinuousRotationServo {
public:
    ContinuousRotationServo();
    //explicit ContinuousRotationServo(uint8_t port);
    void setSpeed(int percent);
    void setDirection(direction_t dir);
private:
    Servo servo;
    direction_t dir;
    uint8_t speed;
};

#endif
