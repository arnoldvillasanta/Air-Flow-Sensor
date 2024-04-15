#include "SensorFIlter.h"

  SensorFilter::SensorFilter(){};
  SensorFilter::~SensorFilter(){};
    
  void SensorFilter::removeDataSpikes(int& airPressure, PressureSensor& airSensor, int& detachedCounter, bool& started) {
    if(airPressure < airSensor.get_lowValue()) {
      if(countSensorMin >= sensorChangeMaxCount) {
        Serial.print("Minimum changed: ");
        Serial.println( airPressure );
        detachedCounter = 0;
        started = true;
        lowPressureDetected = true;
      } else {
        countSensorMin++;
      }
    } else {
      countSensorMin = 0;
    }

    if(airPressure > airSensor.get_highValue()) {
      if(countSensorMax >= sensorChangeMaxCount) {
        Serial.print("Maximum changed: ");
        Serial.println( airPressure );
        detachedCounter = 0;
        started = true;
        highPressureDetected = true;
      } else {
        countSensorMax++;
      }
    } else {
      countSensorMax = 0;
    }
  };