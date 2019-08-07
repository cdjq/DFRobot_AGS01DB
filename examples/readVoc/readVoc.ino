/*!
  *@file readVoc.ino
  *@brief 读取空气中VOC的浓度和芯片的版本号，VOC浓度的单位是PPM(表示一百万份单位质量的溶液中所含溶质的质量).
  *@n 实验现象：我们在开始前读取一次芯片的版本号，以便了解芯片，然后是每3秒读取一次VOC浓度，并打印到串口
  *@n 传感器的分辨率是0.1ppm，传感器的量程时0~100PPM 所以只能测量较窄的范围。
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
  //程序开始前会检测一下IIC是否能正常通信,begin()函数返回0则表示能正常通信
  while (AGS01DB.begin() != 0) {
    Serial.println("初始化芯片失败，请确认芯片连线是否正确");
    delay(1000);
  }
  Serial.println("");
  Serial.print("the version of AGS01DB:");
  Serial.print("0x0");
  /*
    函数名称：readSensorVersion()
    @brief 读取芯片的版本号.
  */
  Serial.println(/*版本号=*/AGS01DB.readSensorVersion(), HEX);
  
}
void loop() {

  //每3秒读取一次voc值,读取间隔应该大于两秒，因为该芯片的采样周期 >=2s，小于两秒则会读到上一次采样的值.
  //若间隔较长时间使用该模块，那么最好预热120s，才会读到较准确的值.
  float voc = AGS01DB.readVocPPM();
  if(voc >= 0){
  Serial.print("the concentration of Voc:");
  /*
    函数名称： AGS01DB.readVocPPM()
    @brief 读取空气中有害气体的浓度.
    @return 返回读取到的VOC浓度值，单位是ppm.
  */
  Serial.print(/*voc=*/voc);
  Serial.println(" PPM");
  }
  delay(3000);
  
}
