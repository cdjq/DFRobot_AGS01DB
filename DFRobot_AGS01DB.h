/*!
 * @file DFRobot_AGS01DB.h
 * @brief 定义DFRobot_AGS01DB 类的基础结构
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-13
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_AGS01DB
 */

#ifndef DFROBOT_AGS01DB_H
#define DFROBOT_AGS01DB_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Wire.h>

//#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define AGS01DB_IIC_ADDR  (0x11)  /*传感器设备的地址*/

//#define ERR_OK             0      //无错误
//#define ERR_DATA_BUS      -1      //数据总线错误
//#define ERR_IC_VERSION    -2      //芯片版本不匹配

class DFRobot_AGS01DB
{
public:
  #define CMD_DATA_COLLECTION_HIGH  0x00     /*获取voc的命令的高位*/
  #define CMD_DATA_COLLECTION_LOW   0x02     /*获取voc的命令的低位*/
  #define CMD_GET_VERSION_HIGH      0x0A     /*获取版本号的命令的高位*/
  #define CMD_GET_VERSION_LOW       0x01      /*获取版本号的命令的低位*/
  /*!
   * @brief 构造函数.
   */
    DFRobot_AGS01DB(TwoWire * pWire = &Wire);
    
    /**
   * @brief 初始化函数
   * @return 返回0表示初始化成功，返回其他值表示初始化失败，返回错误码
   */
    int begin(void);
    
  /**
   * @brief 读取空气中有害气体的浓度.
   * @return 返回读取到的VOC浓度值，单位是ppm.
   */
    float readVocPPM();
    
  /**
   * @brief 读取芯片的版本号.
   * @return 返回读取到的版本号，如0x0B.
   */
    int readSensorVersion();

private:
  /**
   * @brief 检测返回的CRC，是否与数据位的两个数据校验出的CRC8相等.
   * @param data  数据位的数据.
   * @param Num   需要检验数据的个数.
   * @return      返回0表示验证正确，返回其他值表示验证为错误.
   */
    bool   checkCRC8(uint8_t *data, uint8_t Num);
  /**
   * @brief 向传感器芯片写指令.
   * @param pBuf  指令中包含的数据.
   * @param size  指令数据的个数.
   */
    void  writeCommand(const void *pBuf,size_t size);
  /**
   * @brief 向传感器芯片写指令.
   * @param pBuf  指令中包含的数据.
   * @param size  指令数据的个数.
   * @return      返回0表示读取完成，返回其他值表示未能正确读取.
   */
    uint8_t  readData(void *pBuf,size_t size);   
    
    TwoWire *_pWire;
    
};
#endif