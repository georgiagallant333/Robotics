# Robocup2018
Benditlikebeckohm code for Robocup 2018.

This code is divided into the mainProgramUSA, QTR_EEPROM, and Test Programs. 

Within mainProgramUSA its divided into different "states". Depending on the state of the robot and the ball a different code is run. For example, if the robot's photoresistor senses something the state is switched to "HAS_BALL", or if the reflectance sensor sense a line, the intterupt is triggered and the "ON_LINE" state is triggered.

QTR_EEPROM stores the values that qualify as the reflectance sensor sensing a line in EEPROM. We did this because the time it took to calibrate the QTR every time was too long, and it became stressful to calibrate in time.

Test Programs test basic functionality of the robot (IMU, motors, LIDARs, etc) to help with debugging if one aspect of the robot is not working in order to see where the problem stems from.
