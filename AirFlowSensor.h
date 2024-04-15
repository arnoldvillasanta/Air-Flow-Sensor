#ifndef AIRFLOWSENSOR_H
#define AIRFLOWSENSOR_H
#include "Arduino.h"

/*!***************************************************************************************************
- This sensor class holds both autoCalibration and reading process. 
  - Take note that this will change if the pressure sensor will be dual-air port (differential pressure).
 ******************************************************************************************************/

class PressureSensor {
  private:
    int median;                                 /**< Sensor value in the absence of positive/negative pressure  */
    int lowValue;                               /**< Sensor value when negative pressure is applied to the sensor */
    int highValue;                              /**< Sensor value when positive pressure is applied to the sensor  */
    int sensitivity;                            /**< Vendor specific:  Sensitivity of the sensor in detecting pressure change.  */
  public:
    PressureSensor();
    ~PressureSensor();
    //Attributes
    int get_lowValue();                         /**< Retrieves the sensor's lowest limit that triggers inhale data. */
    int get_highValue();                        /**< Retrieves the sensor's highest limit that triggers exhale data. */
    void set_sensitivity(int& s);               /**< Set the sensitivity of the sensor at the start of the systems bootup. */
    // Methods
    void autoCalibrate(int& rc);                /**< Auto Calibrate the sensor based on the Systems Configuration - happens at the start of the bootup. */
    void read_pressure(int& airPressure);       /**< Reads the analog data from the air pressure sensor. */
};

#endif    // AIRFLOWSENSOR_H
