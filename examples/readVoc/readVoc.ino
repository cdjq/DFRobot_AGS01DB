/*!
  *@file readVoc.ino
  *@brief Read the concentration of VOC and chip version. VOC unit: PPM (parts per million)
  * @n Experiment phenomenon: read the chip version before using, then read VOC concentration every 3 seconds and print it out
  * @n on seria port.
  * @n Resolution: 0.1ppm; Measuring range: 0~100PPM 
  *
  *@copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  *@licence     The MIT License (MIT)
  *@author [fengli](li.feng@dfrobot.com)
  *@version  V1.0
  *@date  2019-07-23
  *@get from https://www.dfrobot.com
  *@https://github.com/DFRobot/DFRobot_AGS01DB
*/
#include<DFRobot_AGS01DB.h>
DFRobot_AGS01DB  AGS01DB(&Wire);

void setup() {

  Serial.begin(115200);
  //detect if the IIC communication works, return 0 if it is fine
  while (AGS01DB.begin() != 0) {
    Serial.println("failed to init chip, please check if the chip connection is fine ");
    delay(1000);
  }
  Serial.println("");
  Serial.print("the version of AGS01DB:");
  Serial.print("0x0");
  /*
    Function name: readSensorVersion()
    @brief Read chip version
  */
  Serial.println(/*version=*/AGS01DB.readSensorVersion(), HEX);
  
}
void loop() {

  //Read VOC every 3 seconds, and the interval should be more than 2s since the sampling cycle of the chip >=2s. If it is set to less
  //than 2s, the reading will be one sampled at the last time. 
  //Please pre-heat the deivce for 120s if using it after a long time to get more accurate readings.
  float voc = AGS01DB.readVocPPM();
  if(voc >= 0){
  Serial.print("the concentration of Voc:");
  /*
    Function name: AGS01DB.readVocPPM()
    @brief Read the concentration of the harmful gas in air.
    @return Return the read VOC value, unit: ppm.
  */
  Serial.print(/*voc=*/voc);
  Serial.println(" PPM");
  }
  delay(3000);
  
}
