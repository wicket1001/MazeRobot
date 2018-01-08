#include "ContiniousRotationServo.h"

ContinuousRotationServo::ContinuousRotationServo() {}

ContinuousRotationServo::ContinuousRotationServo(uint8_t port) {
    servo.attach(port);

    dir = Forward;
    speed = 0;

    setSpeed(speed);
}

void ContinuousRotationServo::setDirection(direction_t dir) {
    this->dir = dir;
    setSpeed(speed);
}

void ContinuousRotationServo::setSpeed(int percent) {
    servo.write(90 + map(percent * (dir * 2 - 1), 0, 100, 0, 90));
}
