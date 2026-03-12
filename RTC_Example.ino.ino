#include <Wire.h> // библиотека для управления устройствами по I2C 
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>
#include <RtcDS1302.h>
#include <ThreeWire.h>
//---------------------------------
// Config for DHT11
DHT11 dht11(2);
//config for RTC
ThreeWire myWire(3,5,6);
RtcDS1302<ThreeWire> Rtc(myWire);
//---------------------------------

LiquidCrystal_I2C lcd(0x27,16,2); // присваиваем имя lcd для дисплея 16х2

//-------------------------------------chars---------------------------------------
byte degree[] = { B00110, B01001, B01001, B00110, B00000, B00000, B00000, B00000 }; // char: °
//---------------------------------------------------------------------------------

unsigned long previousTime = 0;
int interval = 1000;
bool colonState = false;

void setup()
{

  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

  lcd.init(); 
//   lcd.backlight(); 
  lcd.createChar(0,degree);

  //------------------------
      if (!Rtc.IsDateTimeValid()) 
    {
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected())
    {
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Rtc.SetDateTime(compiled);
    }
}  
  
void loop()
{
  if(millis() - previousTime >= interval){
    previousTime = millis();
    colonState = !colonState;
  }
  RtcDateTime now = Rtc.GetDateTime(); // время с RTC сей час

  int temperatureC = dht11.readTemperature();
  //(0 °C × 9/5) + 32 = 32 °F
  int temperatureF = temperatureC * 9/5 + 32; 
  int humidity = dht11.readHumidity();
      //temperature print
      lcd.setCursor(0,0);
      lcd.print("Temp: ");
      lcd.print(temperatureC);
      lcd.write(byte(0));
      lcd.print("C|");
      //time print
      String DayOfWeek;
        switch(now.DayOfWeek()){

        case 0:
            DayOfWeek = "Sun";
            break;

        case 1:
            DayOfWeek = "Mon";
            break;

        case 2:
            DayOfWeek = "Tue";
            break;

        case 3:
            DayOfWeek = "Wed";
            break;

        case 4:
            DayOfWeek = "Thu";
            break;

        case 5:
            DayOfWeek = "Fri";
            break;

        case 6:
            DayOfWeek = "Sat";
            break;
        }
      lcd.setCursor(11,0);
      lcd.print(DayOfWeek);
      lcd.print(now.Day());
      lcd.setCursor(11, 1);
      if(now.Hour()<10){
        lcd.print("0");
        lcd.print(now.Hour());
      } else {
        lcd.print(now.Hour());
      }
      if(colonState){
        lcd.print(":");
      } else {
        lcd.print(" ");
      }
      if(now.Minute()<10){
        lcd.print("0");
        lcd.print(now.Minute());
      } else {
        lcd.print(now.Minute());
      }
      
      //humidity print
      lcd.setCursor(0,1);
      lcd.print("Humid: ");
      lcd.print(humidity);
      lcd.print("%|");
  delay(1000); // one sec
}

