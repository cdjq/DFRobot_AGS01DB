# DFRobot_AGS01DB
AGS01DB is a MEMS VOC gas sensor with calibrated digital signal output. It adopts the special digital module acquisition technology and gas sensing technology to ensure high reliability and long-term stability. With IIC slave working mode, this MEMS gas sensor features low-power consumption, high sensitivity, fast response, low cost and simple drive circuit. It can be used to detect the presence of gases like ethanol, ammonia, sulfides, benzenes vapors, smoke and other harmful gases in the environment with unit PPM (parts per million)
Every kind of gas has different safety values, but most of them are less than 100PPM or even 10PPM<br>
Benzene <br>
Safety value: <1.5 PPM<br>
Low warning: 1.5-3 PPM<br>
High warning: 3-8 PPM<br>
 
![正反面svg效果图](https://github.com/ouki-wang/DFRobot_Sensor/raw/master/resources/images/SEN0245svg1.png)


## Product Link（链接到英文商城）
    SKU：AGS01DB voc气体传感器
   
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

This library can be used to drive AGS01DB chip and read the concentration of the harmful gas in air.

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
    
/**
 * @brief Init function
 * @return Retrun 0 if initialization succeeds, otherwise return non-zero and error code
 */
int begin(void);
    
/**
 * @brief Read the concentration of the harmful gas in air
 * @return Return the read VOC value, unit: ppm
 */
float readVocPPM();
    
/**
 * @brief Read chip version
 * @return Return the read version, such as 0x0B
 */
uint8_t readSensorVersion();
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |      √       |              |             | 
micro:bit        |      √       |              |             | 


## History

- Data 2019-7-23
- Version V0.1


## Credits

Written by fengli(li.feng@dfrobot.com), 2019.7.22 (Welcome to our [website](https://www.dfrobot.com/))





