#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;
DateTime future = 0; // Variable para calcular cuando se debe desactivar la alarma
// CONFIGURACIÓN DE USUARIO
int seconds_alarm = 0; // Segundos alarma
int minutes_alarm =40; // Minutos alarma
int hour_alarm = 9; // Horas alarma. Formato 24h
int day_alarm = 7; // Dia alarma
int month_alarm = 8; // Mes alarma
int year_alarm = 2017; // Año alarma
int weekday_alarm = 1; // Dia de la semana alarma. L(1), M(2), MX(3), J(4), V(5), S(6), D(7)
int alarm_duration = 10; // Tiempo activo de la alarma. Debe ser menor que la próxima alarma.
boolean all_seconds = false; // Alarma para todos los segundos
boolean all_minutes = false; // Alarma para todos los minutos
boolean all_hour = true; // Alarma para todas las horas
boolean all_weekday = true; // Alarma para todos los dias de la semana
boolean all_day = true; // Alarma para todos los dias
boolean all_month = true; // Alarma para todos los meses
boolean all_year = true; // Alarma para todos los años
int LedPin = 12;
// -------------
void setup () {
Wire.begin(); // Inicia el puerto I2C
RTC.begin(); // Inicia la comunicación con el RTC
//RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
pinMode(LedPin, OUTPUT);  // Establece el pin LedPin como salida
digitalWrite(LedPin,HIGH);
Serial.begin(9600); // Establece la velocidad de datos del puerto serie
}
void loop(){

DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
Serial.print(now.year(), DEC); // Año
Serial.print('/');
Serial.print(now.month(), DEC); // Mes
Serial.print('/');
Serial.print(now.day(), DEC); // Dia
Serial.print(' ');
Serial.print(now.hour(), DEC); // Horas
Serial.print(':');
Serial.print(now.minute(), DEC); // Minutos
Serial.print(':');
Serial.print(now.second(), DEC); // Segundos
Serial.println();
if (year_alarm == now.year() || all_year ) {
  if (month_alarm == now.month() || all_month) {
    if (day_alarm == now.day() || all_day) {
      if (weekday_alarm == now.dayOfTheWeek()|| all_weekday) {
        if (hour_alarm == now.hour() || all_hour) {
          if (minutes_alarm == now.minute() || all_minutes) {
            if (seconds_alarm == now.second() || all_seconds) {
            	digitalWrite(LedPin,LOW);
            future = now.unixtime() + alarm_duration;
            Serial.println("------------");
            Serial.println("ALARMA");
            Serial.println("------------");
            }
          }
        }
      }
    }
  }
}
Serial.println(now.unixtime());
Serial.println(future.unixtime());
Serial.println(digitalRead(LedPin));

if (now.unixtime() >= future.unixtime()){
digitalWrite(LedPin, HIGH);
Serial.println("------------");
Serial.println("RESET ALARMA");
Serial.println("------------");

}
delay(1000); // La información se actualiza cada 1 seg.
}
