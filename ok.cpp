#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

//configuración de el relog
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};

//configuración de la pantalla
LiquidCrystal_I2C lcd(0x3f,16,2);
char texto[10];

//variables de reles
 int pin[]={
		  5,6,7,8,9,10,11,12
 };
 int pinTotal=8;

void setup () {
  lcd.init();
  lcd.backlight();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  for (int var = 0; var < pinTotal ; ++var) {
	pinMode(pin[var],OUTPUT);
}
  for (int var = 0; var < pinTotal; ++var) {
	digitalWrite(pin[var],LOW);
}
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
