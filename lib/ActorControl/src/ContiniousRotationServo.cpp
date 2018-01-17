#include "ContiniousRotationServo.h"

/**
 * The default constructor for a Continuous Rotation Servo.
 *
 * @param port The port of the Servo.
 */
ContinuousRotationServo::ContinuousRotationServo(/*uint8_t port*/) {
    servo.attach(2);//((int)port);
    Serial.println("asdf");

    dir = Forward;
    speed = 0;

    setSpeed(speed);
}

/**
 * Set the direction of the Servo.
 *
 * @param dir An direction_t enum, where you can set Backward (0) and Forward (1).
 */
void ContinuousRotationServo::setDirection(direction_t dir) {
    this->dir = dir;
    setSpeed(speed);
}

/**
 * Set the speed percentage from 0 - 100.
 *
 * @param percent The speed percentage of the Servo.
 */
void ContinuousRotationServo::setSpeed(int percent) {
    Serial.print("SetSpeed ");
    Serial.println(percent);
    int a = 90 + map(percent * (dir * 2 - 1), 0, 100, 0, 90);
    Serial.println(a);
    servo.write(a);
}
