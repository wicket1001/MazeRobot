
#include "ActorControl.h"

ActorControl::ActorControl(uint8_t port) {
    thermoServo.attach(3);
    ejectionServo = ContinuousRotationServo(port);
}
