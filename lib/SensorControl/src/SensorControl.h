#ifndef __SENSOR_CONTROL_H__
#define __SENSOR_CONTROL_H__

#include <Arduino.h>
#include <Wire.h>
//#include "../lib/APDS_9960/src/SparkFun_APDS_9960.h"
#include "../../MPU-9250-DMP/src/SparkFunMPU9250-DMP.h"
#include "../../MLX90614/src/SparkFunMLX90614.h"
#include "../../APDS-9960/src/SparkFun_APDS9960.h"
#include "HC_SR04.h"

typedef struct {
    double object;
    double ambient;
} temp_t;

class SensorControl {
public:
    SensorControl();
    uint8_t init();
    String getErrorMessage();

    uint8_t getColors(uint16_t *);
    temp_t *getTemperature();
    uint8_t getAccel(float *arr);
    uint8_t getGyro(float *arr);
    uint8_t getMag(float *arr);
private:
    SparkFun_APDS9960 apds;
    IRTherm therm;
    MPU9250_DMP _10dof;

    HC_SR04 us;

    void setErrorMessage(String error);
    uint8_t update10Dof();

    String err;
    temp_t temp;
};

#endif
