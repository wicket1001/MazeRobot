/**
 * @author Harald Moritz
 * A library to summarize all Sensors.
 */
#include "SensorControl.h"

/**
 * A constructor to enable the SensorControl library.
 * Please call init for full initialisation.
 */
SensorControl::SensorControl() {
    us = HC_SR04();
}

/**
 * Initialise the I2C Sensors.
 *
 * @return If the initialisation worked (1) or was aborted (0). See getErrorMessage for full error message.
 */
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

    //Serial.println("Begin");
    //_10dof.dmpBegin(DMP_FEATURE_GYRO_CAL | DMP_FEATURE_SEND_CAL_GYRO, 10);

    Serial.println("End");
    delay(500);

    return 1;
}

/**
 * Get the error message if an error occurred during the initialisation.
 *
 * @return The error message which occurred last.
 */
String SensorControl::getErrorMessage() {
    return err;
}

/**
 * Set the last error message.
 *
 * @param error The last error that occurred.
 */
void SensorControl::setErrorMessage(String error) {
    err = error;
}

/**
 * Get the colors from the APDS Sensor as uint16_t array.
 *
 * @param arr An uint16_t array to store the colors in.
 * @return If it worked (1) or if it didn't work (0).
 */
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

/**
 * Get the Temperature of the MLX90614 Sensor.
 *
 * @return The temp_t struct with the temperature of the object (object) and the sensor (ambient).
 */
temp_t *SensorControl::getTemperature() {
    if (therm.read()) {
        temp.object = therm.object();
        Serial.println(therm.object());
        temp.ambient = therm.ambient();
        return &temp;
    } else {
        return NULL;
    }
}

/**
 * Updates the values of the 10 dof.
 *
 * @return If it worked (1) or if it didn't work (0).
 */
uint8_t SensorControl::update10Dof() {
    while (!_10dof.dataReady()) { }
    if (_10dof.dataReady()) {
        _10dof.update(UPDATE_ACCEL | UPDATE_GYRO | UPDATE_COMPASS);
        return 1;
    } else {
        return 0;
    }
}

/**
 * Get the Accelerometer values of the MPU-9250-DMP.
 *
 * @param arr The float array to store in.
 * @return If it worked (1) or if it didn't work (0).
 */
uint8_t SensorControl::getAccel(float *arr) {
    uint8_t err = _10dof.updateAccel();
    arr[0] = _10dof.calcAccel(_10dof.ax);
    arr[1] = _10dof.calcAccel(_10dof.ay);
    arr[2] = _10dof.calcAccel(_10dof.az);
    return err;
}

/**
 * Get the Gyroscopic values of the MPU-9250-DMP.
 *
 * @param arr The float array to store in.
 * @return If it worked (1) or if it didn't work (0).
 */
uint8_t SensorControl::getGyro(float *arr) {
    uint8_t err = _10dof.updateGyro();
    arr[0] = _10dof.calcGyro(_10dof.gx);
    arr[1] = _10dof.calcGyro(_10dof.gy);
    arr[2] = _10dof.calcGyro(_10dof.gz);
    Serial.println(err);
    return err;
}

/**
 * Get the Magnetometer values of the MPU-9250-DMP.
 *
 * @param arr The float array to store in.
 * @return If it worked (1) or if it didn't work (0).
 */
uint8_t SensorControl::getMag(float *arr) {
    uint8_t err = _10dof.updateCompass();
    Serial.println(err);
    arr[0] = _10dof.calcMag(_10dof.mx);
    arr[1] = _10dof.calcMag(_10dof.my);
    arr[2] = _10dof.calcMag(_10dof.mz);
    return err;
}

