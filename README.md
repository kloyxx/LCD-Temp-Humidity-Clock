# Arduino Weather Station

Displays **temperature**, **humidity**, **time**, and **day of the week** on a **16x2 I2C LCD** using **DHT11** and **DS1302 RTC**.  

## Features

- Temperature in °C (with degree symbol)  
- Humidity (%)  
- Real-time clock with **blinking colon**  
- Day of the week and date  
- I2C LCD for simple wiring  

## Hardware

- Arduino UNO  
- DHT11 sensor  
- DS1302 RTC module  
- 16x2 I2C LCD  
- Jumper wires  

## Libraries

- Wire  
- LiquidCrystal_I2C  
- DHT11  
- RtcDS1302  
- ThreeWire  

## Wiring

**DHT11:** DATA → D2, VCC → 5V, GND → GND  
**DS1302:** SCLK → D6, DAT → D5, RST → D3, VCC → 5V, GND → GND  
**LCD I2C:** SDA → A4, SCL → A5, VCC → 5V, GND → GND  

## Example Display

Temp:24°C Fri13
Humid:60% 21:48


## Notes

- RTC time is set automatically using compilation time (`__DATE__`, `__TIME__`)  
- Use `lcd.backlight()` to enable LCD backlight  
- 9V battery works for short-term testing
