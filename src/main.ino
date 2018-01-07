#include <Arduino.h>

#include "../lib/SerialCommunication/src/SerialCommunication.h"

#include "../lib/SensorControl/src/SensorControl.h"

//#include "../lib/SensorControl/lib/APDS_9960/src/Sparkfun_APDS_9960.h"
//#include "../lib/SensorControl/lib/MLX90614/src/MLX90614.h"
//#include "../lib/SensorControl/lib/MPU-9250-DMP/src/MPU9250-DMP.h"
//#include "../lib/SensorControl/src/HC_SR04.h"


#include "../lib/ActorControl/src/ActorControl.h"

#include "../lib/ActorControl/src/ContiniousRotationServo.h"
#include "../lib/ActorControl/src/WS2812B.h"


// SERIAL
SerialCommunication ser;

//SENSOR
uint16_t colors[4];
float accel[3];
float gyro[3];
float mag[3];
SensorControl sc = SensorControl();
char serIn[300];
char serOut[300];
temp_t *t;
// Button starter = Button(4);
//HC_SR04 hc_sr04 = HC_SR04();
double distances[4];

//ACTOR
//
// WS2812B rgb = WS2812B(8, 9, 10); // TODO check Pins

//ContinuousRotationServo crs(2);

void setup() {
    ser = SerialCommunication();
}
/*
void sensorSetup() {
    if ( sc.init() ) {
        Serial.println("Initialized.");
    }
    else {
        Serial.println("Initalization error.");
        exit(1);
    }
}

void actorSetup() {

}
*/

boolean equals(char* str1, char* str2) {
    return strcmp(str1, (char*) str2) == 0;
}

void loop() {
    while (ser.isEmpty()) { }
    ser.read(serIn);
    if (equals(serIn, ">getTemp") == 0) {
        if ((t = sc.getTemperature())) {
            sprintf(serOut, "<temp:%.2f", t->object); // <temp:12.34
        } else {
            sprintf(serOut, "<temp:null");
        }
    } else if (equals(serIn,  ">getAccel")) {
        if (sc.getAccel(accel)) {
            sprintf(serOut, "<accel:%.6f,%.6f,%.6f", accel[0], accel[1], accel[2]);
        } else {
            sprintf(serOut, "<accel:null");
        }
    } else if (equals(serIn, ">getGyro")) {
        if (sc.getGyro(gyro)) {
            sprintf(serOut, "<gyro:%.6f,%.6f,%.6f", gyro[0], gyro[1], gyro[2]);
        } else {
            sprintf(serOut, "<gyro:null");
        }
    } else if (equals(serIn, ">getMag")) {
        if (sc.getMag(mag)) {
            sprintf(serOut, "<gyro:%.6f,%.6f,%.6f", mag[0], mag[1], mag[2]);
        } else {
            sprintf(serOut, "<gyro:null");
        }
    } else if (equals(serIn, ">getColors")) {
        if (sc.getColors(&colors)) {
            sprintf(serOut, "<colors:%i,%i,%i", colors[0], colors[1], colors[2]);
        } else {
            sprintf(serOut, "<colors:null");
        }
    } else {
        sprintf(serOut, "<null");
    }
    ser.write(serOut);
    memset(&serIn[0], 0, sizeof(serIn));
    // sprintf(serOut, "Servas");
/*
    for (int i = 0; i < 100; i ++) {
        crs.setSpeed(i);
        delay(100);
    }
*/

    //normal();
    //special();

    //sensorLoop();
    //actorLoop();
    //rgbTest();
    //buttonTest();
}
/*
void normal() {
    uint8_t trigger = 6;
    uint8_t echo = 2;
    hc_sr04.measureOne(trigger, echo);
}

void special() {
    hc_sr04.getDistances(distances);
    int length = sizeof(distances) / sizeof(distances[0]);
    Serial.println("Distances from getDistances: ");
    for (int i = 0; i < length; ++i) {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(distances[i]);
    }
}


void sensorLoop() {
    if (sc.getColors(colors)) {
        sprintf(serIn, "Ambient: %5d Red: %3d Green: %3d Blue: %3d", colors[0], colors[1], colors[2], colors[3]);
        Serial.println(serIn);
        delay(100);
    }
    if ((t = sc.getTemperature())) {
        Serial.println(t->object);
    }
}

void actorLoop() {

    crs.setSpeed(0);
    delay(2000);
//    crs.setSpeed(100);
//    delay(500);
//    crs.setDirection(Backward);
//    delay(500);
//    crs.setSpeed(10);
//    delay(500);
//    crs.setDirection(Forward);
//    delay(500);
}

void rgbTest() {
    for (uint8_t i = 0; i < 360; ++i) {
        rgb.setColor(i);
        delay(10);
    }
}
*/
// TODO Button Test


/*
#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  rainbow(20);
  rainbowCycle(20);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
 */
