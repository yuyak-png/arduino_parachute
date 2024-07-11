#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Servo.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
float xg;
float yg;
float zg;
int i;
int pos = 0;
Servo servo_9;

void setup(void)
{
#ifndef ESP8266
  while (!Serial);
#endif
  Serial.begin(9600);

  if(!accel.begin())
  { 
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  accel.setRange(ADXL345_RANGE_16_G);
  Serial.println("");

  pinMode(13,OUTPUT);
  servo_9.attach(9, 500, 2500);
  servo_9.write(pos = 0);
}

void loop(void)
{
  sensors_event_t event; 
  accel.getEvent(&event);
  xg = abs(event.acceleration.x);
  yg = abs(event.acceleration.y);
  zg = abs(event.acceleration.z);
  
  if (xg >= 30 || yg >= 30 || zg >= 30) {
    digitalWrite(13,HIGH);
    for(i = 0; i < 3; i++){
      for (pos = 0; pos <= 180; pos += 10) {
      servo_9.write(pos);
      delay(15);
      }
      for (pos = 180; pos >= 0; pos -= 10) {
      servo_9.write(pos);
      delay(15); 
      }
    }
    
  } else {
    digitalWrite(13,LOW);
  }
  delay(10);
}
