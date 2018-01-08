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

class ActorControl {
public:
    explicit ActorControl(uint8_t port);

    Servo thermoServo;
    ContinuousRotationServo ejectionServo;

    void init();
private:
};

#endif
