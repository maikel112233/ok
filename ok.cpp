#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

//configuración de el relog
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"DOMINGO", "LUNES", "MARTES", "MIERCOLES", "JUEVES", "VIERNES", "SABADO"};

//configuración de la pantalla
LiquidCrystal_I2C lcd(0x3f,16,2);
char texto[10];

//variables de reles
 int pin[]={
		  5,6,7,8,9,10,11,12
 };
 int pinTotal=8;
 int horas=21;
 int minutos=4;
void setup () {
  lcd.init();
  lcd.backlight();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  for (int var = 0; var < pinTotal ; ++var) {
	pinMode(pin[var],OUTPUT);
}
  for (int var = 0; var < pinTotal; ++var) {
	digitalWrite(pin[var],HIGH);
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

   if(now.hour()==horas && now.minute()==minutos){
	   digitalWrite(pin[0],LOW);
	   lcd.setCursor(0,0);
	   lcd.print("JARDINERAS UNO  ");
   }else if(now.hour()==horas && now.minute()==minutos+1){
	   digitalWrite(pin[0],HIGH);
	   digitalWrite(pin[1],LOW);
	   lcd.setCursor(0,0);
	   lcd.print("JARDINERAS DOS  ");
   }else if(now.hour()==horas && now.minute()==minutos+2){
	   digitalWrite(pin[1],HIGH);
   }



    delay(1000);
}
