/*
 This code is made for an agricultural Arduino feedback system that monitors and controls temperature and humidity.
 The system works to adjust the temperature and humidity inside a green house according to certain conditions,
 to give the best growing environment for potato plants.
 Authors: Capstone Group 22211 - Sharkya STEM School
 Mousa Mohammed - Mahmoud Ahmed - Omar Adel
 Date Modified: 12th April, 2023
 */

// Identifying and assigning Variables.
unsigned long PreviousTime=0;
const unsigned long interval=1500;
unsigned long timer;
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <DHT.h>;
#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float t;
float h;
void setup() {
// Giving the pins the signal to begin in the code to be able to give them arguments.
 lcd.init();
 lcd.backlight();
 dht.begin();
 pinMode(7, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(3, OUTPUT);
}

void loop() {
  digitalWrite(6, HIGH);
    h = dht.readHumidity();
    t = dht.readTemperature();
  timer=millis();
//send the readings of temperature and humidity every 1.5 seconds.
  if(timer-PreviousTime>=interval){
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(t);
    lcd.print(" C");
    lcd.setCursor(0, 1);
    lcd.print("Humid:");
    lcd.print(h);
    lcd.print(" %");
    PreviousTime=timer;
  }
// setting the condiitons of temperature and humidity's increment or decrement.
    if(t>20) digitalWrite(7, LOW);
    else digitalWrite(7, HIGH);
// If the temperature is higher than the limit, open a cooling fan to decrease it.
    if(t<16) digitalWrite(6, LOW);
    else digitalWrite(6, HIGH);
// If the temperature is lower than the limit, open a TEC to heat up the box and increase it.
    if(h<80) digitalWrite(3, HIGH);
    else digitalWrite(3, LOW);
// If the humidity is lower than the limit, open an air humidifier to increase it.
    if(h>95){
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
// If the humidity is higher than the limit, the box will be heated by the TEC with air stirring by the fan to decrease it.
   }
 }
