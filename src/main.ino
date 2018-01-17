#include <Arduino.h>
#include <stdio.h>
#include <Servo.h>

#include "../lib/SerialCommunication/src/SerialCommunication.h"
#include "../lib/SensorControl/src/SensorControl.h"
#include "../lib/ActorControl/src/ActorControl.h"

// SERIAL
SerialCommunication ser;
char serIn[300];
char serOut[300];

//Servo s;

// SENSOR
SensorControl sc;
uint16_t colors[4];
float arr[3];
temp_t *t;
double distances[4];

// ACTOR
ActorControl act;
int num;

void setup() {
    ser = SerialCommunication();
//    s.attach(2);
    sc = SensorControl();
    act = ActorControl();
    sc.init();
}

boolean equals(char* str1, char* str2) {
    return strncmp(str1, str2, strlen(str2)) == 0;
}

void loop() {
    memset(&serIn, 0, sizeof(serIn));
    memset(&serOut, 0, sizeof(serOut));
    while (ser.isEmpty()) { }
    ser.read(serIn);
    ser.write(serIn);
    if (equals(serIn, ">getTemp")) {
        if ((t = sc.getTemperature())) {
            sprintf(serOut, "<temp:%i.%02i", (int)t->object, (int)((t->object-(int)t->object)*100)); // <temp:12.34
        } else {
            sprintf(serOut, "<temp:null");
        }
    } else if (equals(serIn,  ">getAccel")) {
        if (sc.getAccel(arr)) {
            sprintf(serOut, "<accel:%i.%06i,%i.%06i,%i.%06i",
                    (int)arr[0], (int)((arr[0]-(int)arr[0]*1000000)),
                    (int)arr[1], (int)((arr[1]-(int)arr[1]*1000000)),
                    (int)arr[2], (int)((arr[2]-(int)arr[2]*1000000)));
        } else {
            sprintf(serOut, "<accel:null");
        }
    } else if (equals(serIn, ">getGyro")) {
        if (sc.getGyro(arr)) {
            sprintf(serOut, "<gyro:%i.%06i,%i.%06i,%i.%06i",
                    (int)arr[0], (int)((arr[0]-(int)arr[0]*1000000)),
                    (int)arr[1], (int)((arr[1]-(int)arr[1]*1000000)),
                    (int)arr[2], (int)((arr[2]-(int)arr[2]*1000000)));
        } else {
            sprintf(serOut, "<gyro:null");
        }
    } else if (equals(serIn, ">getMag")) {
        if (sc.getMag(arr)) {
            sprintf(serOut, "<mag:%i.%06i,%i.%06i,%i.%06i",
                    (int)arr[0], (int)((arr[0]-(int)arr[0]*1000000)),
                    (int)arr[1], (int)((arr[1]-(int)arr[1]*1000000)),
                    (int)arr[2], (int)((arr[2]-(int)arr[2]*1000000)));
        } else {
            sprintf(serOut, "<mag:null");
        }
    } else if (equals(serIn, ">getColors")) {
        if (sc.getColors((uint16_t *)colors)) {
            sprintf(serOut, "<colors:%i,%i,%i", colors[0], colors[1], colors[2]);
        } else {
            sprintf(serOut, "<colors:null");
        }
    } else if (equals(serIn, ">setThermo:")) {
        sscanf(serIn, ">setThermo:%i", &num);
        act.thermoServo.write(num);
        sprintf(serOut, "<thermo:%i", num);
    } else if (equals(serIn, ">setEjectSpeed:")) {
        sscanf(serIn, ">setEjectSpeed:%i", &num);
        //act.ejectionServo.setSpeed(num);
        //s.write(num);
        sprintf(serOut, "<speed:%i", num);
    } else if (equals(serIn, ">setEjectDirection:")) {
        sscanf(serIn, ">setEjectDirection:%i", &num);
        act.ejectionServo.setDirection((direction_t) num);
        sprintf(serOut, "<direction:%i", num);
    } else {
        sprintf(serOut, "<null");
    }
    ser.write(serOut);
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