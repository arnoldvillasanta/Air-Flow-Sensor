/*! \mainpage Code Demo for C++ in Embedded Systems (Stripped-down version from original project repository) 
 *
 * The codes in this demo are recreated from a previous project (December, 2019) which is undergoing a US Patent Application and under an NDA agreement with client. \n
 * Project:   <b> SYSTEMS AND METHODS FOR MONITORING AND MANAGEMENT OF A PATIENT'S OXYGEN THERAPY AND BREATHING </b> \n
 * Client:    Dr. Gregg Soifer (Georgia, USA) \n
 * Patent Application: https://patents.justia.com/patent/20210259576 \n \n
 * 
 * @author  ARNOLD VILLASANTA \n
 *
 * \subsection note1 SOLID principle 
 *    - Single Responsibility
 *      - Codes separated in modular classes.  Can be separated further into sub-classes if needed.
 *      - The .ino file is the main controller (LOOP block) while the object values are initialized at SETUP block. \n \n
 *    - Open Closed
 *      - The requirement is straightforward and there might not be additional features within the code modules.
 *      - If there will be, then I suggest using the DECORATOR design pattern. \n \n
 *    - Liskov Substitution
 *      - This is not yet required, unless the Analog pressure sensor will be replaced by MEMS pressure sensor in the future.
 *      - If so, a parent class will be created for the AirFlowSensor. \n \n
 *    - Interface Segregation
 *      - Not applied for this simple demo (no interface)  
 *      - Original project codes have Interfaces for the sensor, wifi connection, and data monitor.  \n \n
 *    - Dependency Injection
 *      - No abstraction applied for this simple demo (no interface)
 *      - Original project codes have implemented DI for the sensor and for the connectivity (wifi/lorawan/bluetooth) as far as I can remember.  \n \n
 *  
 *    ![](airSensor.jpg)    ![](logfile.png)
 */


/*
  Air Flow Sensor
  Author: Arnold Villasanta (Finland)  2024-3  1:11 pm

  Version:  1.0
*/

// For the Display, connect it via I2C using the Arduino Wire:
#include <Wire.h>               
#include "HT_SH1107Wire.h"
#include "AirFlowSensor.h"
#include "Monitor.h"
#include "SensorFilter.h"
#include "SystemParameters.h"



// Instantiate required 
SH1107Wire  display(0x3c, 500000, SDA, SCL ,GEOMETRY_128_64,GPIO10); // addr, freq, sda, scl, resolution, rst
PressureSensor airSensor;
Monitor monitor;
SensorFilter sensorFilter;
SystemParameters sysParam;


// Setup
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Systems sysParam.started.");
  display.init();
  monitor.drawMessage(display, "Please wait", " Setup... ");
  airSensor.set_sensitivity(sysParam.sensorSensitivity);
  airSensor.autoCalibrate(sysParam.sensorCalibrationCycle);
  monitor.drawMessage(display, "Monitoring:", "  Ready!  ");
}



void loop() {
  airSensor.read_pressure(sysParam.airPressure);
  sensorFilter.removeDataSpikes(sysParam.airPressure, airSensor, sysParam.detachedCounter, sysParam.started);
  if(sensorFilter.lowPressureDetected) {
    monitor.drawMessage(display, "Monitoring:", "  Inhale ");  
    sensorFilter.lowPressureDetected = false;
  } 
  else if(sensorFilter.highPressureDetected) {
    monitor.drawMessage(display, "Monitoring:", "  Exhale ");
    sensorFilter.highPressureDetected = false;
  }
  else if(sysParam.started && sysParam.airPressure > airSensor.get_lowValue() && sysParam.airPressure < airSensor.get_highValue() && sysParam.detachedCounter < sysParam.detachedTime) {
    sysParam.detachedCounter += 1;
  }
  if (sysParam.detachedCounter >= sysParam.detachedTime && sysParam.started) {
    monitor.drawMessage(display, "Monitoring:", " Detached! ");
    Serial.println("The Nassal Cannula was detached.");
    sysParam.detachedCounter = 0;
  }
  delay (sysParam.delay_time);
}