#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

//configuración de el relog
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = { "DOMINGO  ", "LUNES    ", "MARTES   ",
		"MIERCOLES", "JUEVES   ", "VIERNES  ", "SABADO   " };

//configuración de la pantalla
LiquidCrystal_I2C lcd(0x3f, 16, 2);
char texto[10];

//variables de reles
int pin[] = { 5, 6, 7, 8, 9, 10, 11, 12 };
int pinTotal = 8;
int horas = 18;
int minutos = 50;
void setup() {
	Serial.begin(9600);
	lcd.init();
	lcd.backlight();
	//rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	for (int var = 0; var < pinTotal; ++var) {
		pinMode(pin[var], OUTPUT);
	}
	for (int var = 0; var < pinTotal; ++var) {
		digitalWrite(pin[var], HIGH);
	}
}

void loop() {
	DateTime now = rtc.now();
	lcd.setCursor(0, 0);
	lcd.print(now.year(), DEC);
	lcd.print('/');
	lcd.print(now.month(), DEC);
	lcd.print('/');
	lcd.print(now.day(), DEC);
	lcd.print(" ");
	lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
	//lcd.print(") ");
	lcd.setCursor(0, 1);
	sprintf(texto, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
	lcd.print(texto);
	char c = Serial.read();
	if ((now.hour()==horas && now.minute()==minutos)||(c=='1'))
		digitalWrite(12, LOW);
	if (c == '2')
		digitalWrite(11, HIGH);
	if (c == '3')
		digitalWrite(10, HIGH);
	if (c == '4')
		digitalWrite(9, HIGH);
	if (c == '5')
		digitalWrite(8, HIGH);
	if (c == '6')
		digitalWrite(7, HIGH);
	if (c == '7')
		digitalWrite(6, HIGH);
	if (c == '8')
		digitalWrite(5, HIGH);
	if ((now.hour()==horas && now.minute()==minutos+1)||(c=='a'))
		digitalWrite(12, HIGH);
	if (c == 'B')
		digitalWrite(11, LOW);
	if (c == 'C')
		digitalWrite(10, LOW);
	if (c == 'D')
		digitalWrite(9, LOW);
	if (c == 'E')
		digitalWrite(8, LOW);
	if (c == 'F')
		digitalWrite(7, LOW);
	if (c == 'G')
		digitalWrite(6, LOW);
	if (c == 'H')
		digitalWrite(5, LOW);

	delay(1000);
}
