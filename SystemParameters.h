#ifndef SYSTEMPARAMETERS_H
#define SYSTEMPARAMETERS_H


/*!***************************************************************************
- Simplified Systems Object that hold all default and active parameters. 
- Not ideal but can do for this demo.
******************************************************************************/

class SystemParameters {
  public:
    //System timing
    int delay_time              = 5;          /**<  Specify the wait time before looping back to the start of the process.  Adjust this as necessary.  */
    //System State    
    boolean started             = false;      /**<  Keeps track of the start status of the system.  Needed as not to trigger false alarm when the system is not used but powered up.*/
    int airPressure             = 0;          /**<  Track real-time air pressure data. */
    int detachedCounter         = 0;          /**<  Track real-time detached status - no high and low data from sensor. */
    int detachedTime            = 2000;       /**<  The waiting limit of the nasal cannula detached from the user/patient.  */
    //Pressure Sensor Default   
    int sensorCalibrationCycle  = 200;        /**<  The number of cycles that the calibration will try to detect pressure and get the average for the median value of pressure. */
    int sensorSensitivity       = 3;          /**<  The step value from median value to low- and high pressure variance when no pressure is applied to the sensor.  
                                                    This is usually indicated in the vendor's product documentations. */
};

#endif   //SYSTEMPARAMETERS_H