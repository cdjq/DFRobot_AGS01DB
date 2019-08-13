/*!
 * @file DFRobot_AGS01DB.h
 * @brief Define the basic structure of class DFRobot_AGS01DB 
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

#define AGS01DB_IIC_ADDR  (0x11)  /*sensor IIC address*/

//#define ERR_OK             0      //ok
//#define ERR_DATA_BUS      -1      //error in data bus
//#define ERR_IC_VERSION    -2      //chip version mismatch

class DFRobot_AGS01DB
{
public:
  #define CMD_DATA_COLLECTION_HIGH  0x00     /*Get the high byte of command voc*/
  #define CMD_DATA_COLLECTION_LOW   0x02     /*Get the low byte of command voc*/
  #define CMD_GET_VERSION_HIGH      0x0A     /*Get the high byte of command Version*/
  #define CMD_GET_VERSION_LOW       0x01      /*Get the low byte of command Version*/
  /*!
   * @brief Constructor 
   */
    DFRobot_AGS01DB(TwoWire * pWire = &Wire);
    
    /**
   * @brief init function
   * @return Return 0 if initialization succeeds, otherwise return non-zero and error code.
   */
    int begin(void);
    
  /**
   * @brief Read the concentration of the harmful gas in air
   * @return Return the read VOC value, unit: ppm.
   */
    float readVocPPM();
    
  /**
   * @brief Read chip version 
   * @return Return the read version, such as 0x0B.
   */
    int readSensorVersion();

private:
  /**
   * @brief Detect if the returned CRC is equal to the CRC8 caculated through the two data in data byte.
   * @param data  Data in data byte
   * @param Num   The number of the data to be checked 
   * @return      Return 0 if the check is correct, otherwise return non-zero.
   */
    bool   checkCRC8(uint8_t *data, uint8_t Num);
  /**
   * @brief Write command into sensor chip 
   * @param pBuf  Data included in command
   * @param size  The number of the byte of command
   */
    void  writeCommand(const void *pBuf,size_t size);
  /**
   * @brief Write command into sensor chip 
   * @param pBuf  Data included in command
   * @param size  The number of the byte of command
   * @return      Return 0 if the reading is done, otherwise return non-zero. 
   */
    uint8_t  readData(void *pBuf,size_t size);   
    
    TwoWire *_pWire;
    
};
#endif
