
#include "ActorControl.h"

ActorControl::ActorControl() {
    thermoServo.attach(3);
    Serial.println("tgvhbjvkdhfbdn");
    ejectionServo = ContinuousRotationServo();
}
