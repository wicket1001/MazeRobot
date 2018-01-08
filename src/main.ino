#include <Arduino.h>
#include <stdio.h>

#include "../lib/SerialCommunication/src/SerialCommunication.h"
#include "../lib/SensorControl/src/SensorControl.h"
#include "../lib/ActorControl/src/ActorControl.h"

// SERIAL
SerialCommunication ser;
char serIn[300];
char serOut[300];

// SENSOR
SensorControl sc;
uint16_t colors[4];
float accel[3];
float gyro[3];
float mag[3];
temp_t *t;
double distances[4];

// ACTOR
ActorControl act = ActorControl((uint8_t)2);
int num;

void setup() {
    ser = SerialCommunication();
    sc = SensorControl();
}

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
        if (sc.getColors((uint16_t *)colors)) {
            sprintf(serOut, "<colors:%i,%i,%i", colors[0], colors[1], colors[2]);
        } else {
            sprintf(serOut, "<colors:null");
        }
    } else if (equals(serIn, ">setEject:")) {
        sscanf(serIn, ">setEject:%i", &num);
        act.thermoServo.write(num);
    } else if (equals(serIn, ">setThermoSpeed:")) {
        sscanf(serIn, ">setThermoSpeed:%i", &num);
        act.ejectionServo.setSpeed(num);
    } else if (equals(serIn, ">setThermoDirection:")) {
        sscanf(serIn, ">setThermoDirection:%i", &num);
        act.ejectionServo.setDirection((direction_t) num);
    } else {
        sprintf(serOut, "<null");
    }
    ser.write(serOut);
    memset(&serIn[0], 0, sizeof(serIn));
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
*/