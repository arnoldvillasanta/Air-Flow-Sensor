#ifndef SENSORFILTER_H
#define SENSORFILTER_H
#include "Arduino.h"
#include "AirFlowSensor.h"


/*!***************************************************************************************************
- ADC pins are susceptible for environment changes thus affecting the sensor readings. 
- The transients (dc spikes) needs to be trimmed out and this is the purpose of this code.
  - 5 consecutive high- or low- values is an ideal assumption for true values (sensorChangeMaxCount)
  - For too noisy sensor or board pins, increase this value as needed.
******************************************************************************************************/

class SensorFilter {
  private:
    int sensorChangeMaxCount = 5;       /**<  The maximum count before the signal is considered valid and probability of spike data is eliminated. */
    int countSensorMin = 0;             /**<  Tracks the number of consecutive triggers to the minimum threshold - inhale data. */
    int countSensorMax = 0;             /**<  Tracks the number of consecutive triggesr to the maximum threshold - exhale data. */
  public:
    SensorFilter();
    ~SensorFilter();
    //Attributes
    bool lowPressureDetected;           /**<  Tracks the real-time status of the low threshold data - inhale. */
    bool highPressureDetected;          /**<  Tracks the real-time status of the high threshold data - exhale. */
    // Methods
    void removeDataSpikes(int& airPressure, PressureSensor& airSensor, int& detachedCounter, bool& started);    /**<  A simplified algorithm to remove unwanted analog signal from the air pressure sensor. */
};




#endif  //SENSORFILTER_H