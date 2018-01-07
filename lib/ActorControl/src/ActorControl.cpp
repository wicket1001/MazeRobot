#include "ActorControl.h"

ActorControl::ActorControl() {
    thermoServo.attach(3);
    //ejectionServo = ContinuousRotationServo(2);
}

void ActorControl::init() {

}
/*
void ActorControl::ejectKit() {
    crs.setSpeed(100);
    delay();
    crs.setSpeed(0);
}
*/