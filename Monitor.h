#ifndef MONITOR_H
#define MONITOR_H
#include "Arduino.h"
#include "HT_SH1107Wire.h"

/*!***************************************************************************************************
- This module handles all methods to write to the LCD or display monitor. 
  - This is a over-simplified implementation which is hard-wired to only 1 specific display.
 ******************************************************************************************************/

class Monitor {
  public:
    Monitor();
    ~Monitor();
    //Attributes
    // Methods
    void drawMessage(SH1107Wire& display, String M1, String M2);    /**<  Writes data to the LCD/Monitor screen based on real time acquisition of pressure sensor.*/
};







#endif   //MONITOR_H