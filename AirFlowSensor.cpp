#include "AirFlowSensor.h"

PressureSensor::PressureSensor(){};
PressureSensor::~PressureSensor(){};

int PressureSensor::get_lowValue() {
  return lowValue;
}
int PressureSensor::get_highValue() {
  return highValue;
}
void PressureSensor::set_sensitivity(int& s) {
  this->sensitivity = s;
}

void PressureSensor::autoCalibrate(int& rc) {
  for(int i = 0; i < rc; i++) {
    median += analogRead(ADC2);
    delay(50);
  }
  median = median/rc;
  lowValue = median - sensitivity;
  highValue = median + sensitivity;
  Serial.println("==================================");
  Serial.println("Air Flow Sensor Settings: ");
  Serial.print  ("   Low Value     :  ");
  Serial.println(lowValue);
  Serial.print  ("   Median Value  :  ");
  Serial.println(median);
  Serial.print  ("   High Value    :  ");
  Serial.println(highValue);
  Serial.println("==================================");
}

void PressureSensor::read_pressure(int& airPressure) {
  airPressure = analogRead(ADC2);
}
