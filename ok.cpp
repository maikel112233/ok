#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
//#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//esto es de que se esta haciendo una prueba
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x3f,16,2);

char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
char texto[10];
void setup () {
  lcd.init();
  lcd.backlight();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

}

void loop () {
    DateTime now = rtc.now();
    lcd.setCursor(0,0);
    lcd.print(now.year(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.day(), DEC);
    lcd.print(" ");
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
   //lcd.print(") ");
   lcd.setCursor(0,1);
   sprintf(texto,"%02d:%02d:%02d",now.hour(),now.minute(),now.second());
   lcd.print(texto);



    delay(1000);
}
