#ifndef __ACTOR_CONTROL_H__
#define __ACTOR_CONTROL_H__

#include <Arduino.h>
#include "ContiniousRotationServo.h"

#define PIN 6

#define NUM_LEDS 1

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)

class ActorControl {
public:
    ActorControl();

    void init();
    //Servo thermoServo;
    //ContinuousRotationServo ejectionServo;
private:

};

#endif
