/*!
 * @file DFRobot_AGS01DB.h
 * @brief Define the basic structure of class DFRobot_AGS01DB
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-13
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_AGS01DB
*/
#include"DFRobot_AGS01DB.h"

DFRobot_AGS01DB::DFRobot_AGS01DB(TwoWire * pWire)
  : _pWire(pWire) {
}

int DFRobot_AGS01DB::begin() {
  _pWire->begin();
  //check if the IIC communication works 
  if (_pWire->requestFrom(AGS01DB_IIC_ADDR, 1) != 1) {
    return -1;
  }
  return 0;
}

float DFRobot_AGS01DB::readVocPPM() {
  uint8_t readCMD[3]={0};
  uint8_t data[3] = {0};
  int voc=-10.0;
  readCMD[0] = CMD_DATA_COLLECTION_HIGH;
  readCMD[1] = CMD_DATA_COLLECTION_LOW;
  int retries = 10;
  // when the returned data is wrong, request to get data again until the data is correct. 
  while(retries--) {
    writeCommand(readCMD, 2);
    readData(data, 3);
    //read data from the sensor, check if VOC data got from the check function is correct. 
    //if it is correct, retrun VOC concentration 
    if (checkCRC8(data, 2) == 1) {
      voc = data[0];
      voc <<= 8;
      voc |= data[1];
      break;
    } else {
      DBG("voc's Crc8 incorrect");
    }
  }
  return voc / 10.0;
}

int DFRobot_AGS01DB::readSensorVersion() {
  uint8_t readCMD[2];
  uint8_t data[2] = {0,0};
  int version = 0;
  int retries = 10;
  readCMD[0] = CMD_GET_VERSION_HIGH;
  readCMD[1] = CMD_GET_VERSION_LOW;
  while (retries--) {
    writeCommand(readCMD, 2);
    readData(data, 2);
    //read data from the sensor, check if the Version data got from the check function is correct.
    if (checkCRC8(data, 1) == 1) {
      version = data[0];
      return version;
    } else {
      DBG("version's Crc8 incorrect");
    }
  }
    return version;
}

bool DFRobot_AGS01DB::checkCRC8(uint8_t *data, uint8_t Num) {
  uint8_t bit, byte, crc = 0xFF;
  // the data of the converted data byte should be identical with the data got from the check function.
  for (byte = 0; byte < Num; byte++)
  {
    crc ^= (data[byte]);
    for (bit = 8; bit > 0; --bit)
    {
      if (crc & 0x80) 
          crc = (crc << 1) ^ 0x31;
      else 
          crc = (crc << 1);
    }
  }
  //compare the caculated crc with the read crc to determine if the reading is correct
  if (crc == data[Num]) { 
    return true;
  } else {
    return false;
  }
}

void DFRobot_AGS01DB::writeCommand(const void *pBuf, size_t size) {
  if (pBuf == NULL) {
    DBG("pBuf ERROR!! : null pointer");
  }

  uint8_t * _pBuf = (uint8_t *)pBuf;
  for (uint8_t i = 0; i < size; i++) {
    _pWire->beginTransmission(AGS01DB_IIC_ADDR);
    _pWire->write(_pBuf[i]);
    _pWire->endTransmission();
   delay(3);
  }
}

uint8_t DFRobot_AGS01DB::readData(void *pBuf, size_t size) {
  if (pBuf == NULL) {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  //read the data returned by the chip
  _pWire->requestFrom(AGS01DB_IIC_ADDR, size);
  uint8_t i = 0;
  for (uint8_t i = 0 ; i < size; i++) {
    _pBuf[i] = _pWire->read();
  }
  //_pWire->endTransmission();
  return 1;
}
