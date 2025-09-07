#include <Servo.h>
Servo rc;
const int trig = 12;
const int echo = 11;
#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

int cambien = 4; 
DHT dht(cambien,DHT11); 
void setup() {
 rc.attach(9);
 pinMode(trig,OUTPUT);
 pinMode(echo,INPUT);
 Serial.begin(9600);
 dht.begin();
  lcd.init();             
  lcd.backlight();
}
void loop() {
unsigned long duration;
int khoangcach;
digitalWrite(trig,0);
delayMicroseconds(2);
digitalWrite(trig,1);
delayMicroseconds(5);
digitalWrite(trig,0);
duration = pulseIn(echo,HIGH);
khoangcach = int(duration/2/29.412);
Serial.print(khoangcach);
Serial.println("cm");
delay(100);

if(khoangcach<5){
 rc.write(100);
 delay(10000);
  rc.write(0);
}
else{
  rc.write(0);
}
 float nhietdo = dht.readTemperature(); 
  float doam = dht.readHumidity(); 

  Serial.print("Nhiệt độ hiện tại: ");
  Serial.println(nhietdo);
  Serial.print("Độ ẩm hiện tại: ");
  Serial.println(doam);
  delay(3000);
  if(nhietdo>50){
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("FIRED");
  } 
  else {
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Nhiet do: ");   
    lcd.print(nhietdo); 
    lcd.setCursor(0,1); 
    lcd.print("Do am: "); 
    lcd.print(doam);  
  }
}