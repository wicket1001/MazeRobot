#ifndef __ACTOR_CONTROL_H__
#define __ACTOR_CONTROL_H__

#include <Arduino.h>
#include "WS2812B.h"
#include "ContiniousRotationServo.h"
#include "MotorControl.h"

typedef struct {
    uint8_t motorPin;
    uint8_t encoderPin;
} motor_t;

typedef struct {
    uint8_t pinRed;
    uint8_t pinGreen;
    uint8_t pinBlue;
} rgb_led_t;

class ActorControl {
public:
    ActorControl();
    void init();
private:
    Servo thermoServo;
    //ContinuousRotationServo ejectionServo(2);
};

#endif
