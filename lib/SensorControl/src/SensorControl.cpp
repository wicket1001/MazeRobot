#include "SensorControl.h"

SensorControl::SensorControl() {
    // uint8_t i = 0;
    us = HC_SR04();
}

uint8_t SensorControl::init() {
    apds = SparkFun_APDS9960();
    if (!apds.init()) {
        setErrorMessage("APDS init doesn't work.");
        return 0;
    }
    if (!apds.enableLightSensor(false)) {
        setErrorMessage("Enable light sensor doesn't work.");
        return 0;
    }

    therm = IRTherm();
    if (!therm.begin()) {
        setErrorMessage("IRTherm begin doesn't work.");
        return 0;
    }
    therm.setUnit(TEMP_C);

    _10dof = MPU9250_DMP();
    if (_10dof.begin() != 0) {
        setErrorMessage("MPU9250_DMP begin doesn't work.");
        return 0;
    }
    _10dof.setSensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS);

    _10dof.setGyroFSR(2000);
    _10dof.setAccelFSR(2);
    _10dof.setLPF(5);
    _10dof.setSampleRate(10);
    _10dof.setCompassSampleRate(10);

    delay(500);

    return 1;
}

String SensorControl::getErrorMessage() {
    return err;
}

void SensorControl::setErrorMessage(String error) {
    err = error;
}

uint8_t SensorControl::getColors(uint16_t *arr) {
    uint16_t ambient_light = 0;
    uint16_t red_light = 0;
    uint16_t green_light = 0;
    uint16_t blue_light = 0;

    if (  !apds.readAmbientLight(ambient_light) ||
          !apds.readRedLight(red_light) ||
          !apds.readGreenLight(green_light) ||
          !apds.readBlueLight(blue_light) ) {
        return 0;
    }

    arr[0] = ambient_light;
    arr[1] = red_light;
    arr[2] = green_light;
    arr[3] = blue_light;

    return 1;
}

temp_t *SensorControl::getTemperature() {
    if (therm.read()) {
        temp.object = therm.object();
        temp.ambient = therm.ambient();
        return &temp;
    } else {
        return NULL;
    }
}

uint8_t SensorControl::update10Dof() {
    if (_10dof.dataReady()) {
        _10dof.update(UPDATE_ACCEL | UPDATE_GYRO | UPDATE_COMPASS);
        return 1;
    } else {
        return 0;
    }
}

uint8_t SensorControl::getAccel(float *arr) {
    uint8_t err = update10Dof();
    arr[0] = _10dof.calcAccel(_10dof.ax);
    arr[1] = _10dof.calcAccel(_10dof.ay);
    arr[2] = _10dof.calcAccel(_10dof.az);
    return err;
}

uint8_t SensorControl::getGyro(float *arr) {
    uint8_t err = update10Dof();
    arr[0] = _10dof.calcGyro(_10dof.gx);
    arr[1] = _10dof.calcGyro(_10dof.gy);
    arr[2] = _10dof.calcGyro(_10dof.gz);
    return err;
}

uint8_t SensorControl::getMag(float *arr) {
    uint8_t err = update10Dof();
    arr[0] = _10dof.calcMag(_10dof.mx);
    arr[1] = _10dof.calcMag(_10dof.my);
    arr[2] = _10dof.calcMag(_10dof.mz);
    return err;
}

