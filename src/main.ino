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

// SENSOR
SensorControl sc;
uint16_t colors[4];
float arr[3];
char double_str0[8];
char double_str1[8];
char double_str2[8];
temp_t *t;
double distances[4];

// ACTOR
ActorControl act;
int num;

void setup() {
    Serial.println("asdf");
    ser = SerialCommunication();
    sc = SensorControl();
    act = ActorControl();
    sc.init();
    act.init();
    Serial.println("fdsa");
}

boolean equals(char* str1, char* str2) {
    return strncmp(str1, str2, strlen(str2)) == 0;
}

void loop() {
    memset(&serIn, 0, sizeof(serIn));
    memset(&serOut, 0, sizeof(serOut));
    while (ser.isEmpty()) { }
    Serial.println("Hey");
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
            dtostrf(arr[0], 6, 5, double_str0);
            dtostrf(arr[1], 6, 5, double_str1);
            dtostrf(arr[2], 6, 5, double_str2);
            sprintf(serOut, "<accel:%s,%s,%s", double_str0, double_str1, double_str2);
        } else {
            sprintf(serOut, "<accel:null");
        }
    } else if (equals(serIn, ">getGyro")) {
        if (sc.getGyro(arr)) {
            dtostrf(arr[0], 6, 5, double_str0);
            dtostrf(arr[1], 6, 5, double_str1);
            dtostrf(arr[2], 6, 5, double_str2);
            sprintf(serOut, "<accel:%s,%s,%s", double_str0, double_str1, double_str2);
        } else {
            sprintf(serOut, "<gyro:null");
        }
    } else if (equals(serIn, ">getMag")) {
        if (sc.getMag(arr)) {
            dtostrf(arr[0], 6, 5, double_str0);
            dtostrf(arr[1], 6, 5, double_str1);
            dtostrf(arr[2], 6, 5, double_str2);
            sprintf(serOut, "<accel:%s,%s,%s", double_str0, double_str1, double_str2);
        } else {
            sprintf(serOut, "<mag:null");
        }
    } else if (equals(serIn, ">getColors")) {
        if (sc.getColors((uint16_t *)colors)) {
            sprintf(serOut, "<colors:%i,%i,%i", colors[0], colors[1], colors[2]);
        } else {
            sprintf(serOut, "<colors:null");
        }
    } else if (equals(serIn, ">setColor:")) {
        sscanf(serIn, ">setColor:%i", &num);
        // act.setColor();
        sprintf(serOut, "<setColor:%i", &num);
    } else if (equals(serIn, ">setThermo:")) {
        sscanf(serIn, ">setThermo:%i", &num);
        //act.thermoServo.write(num);
        sprintf(serOut, "<thermo:%i", num);
    } else if (equals(serIn, ">setEjectSpeed:")) {
        sscanf(serIn, ">setEjectSpeed:%i", &num);
        //act.ejectionServo.setSpeed(num);
        //s.write(num);
        sprintf(serOut, "<speed:%i", num);
    } else if (equals(serIn, ">setEjectDirection:")) {
        sscanf(serIn, ">setEjectDirection:%i", &num);
        //act.ejectionServo.setDirection((direction_t) num);
        sprintf(serOut, "<direction:%i", num);
    } else {
        sprintf(serOut, "<null");
    }
    ser.write(serOut);
}
