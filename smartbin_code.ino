#include <TFMPlus.h>
#include "DHT.h"
#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservo1; 
Servo myservo2;
int pos = 0; 
SoftwareSerial sen4(10,11);
TFMPlus s1;
TFMPlus s2;
TFMPlus s3;
TFMPlus s4;
int db1,db2,db3,db4;
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int SENSOR_PIN1 = 7;
const int SENSOR_PIN2 = 8;
const int SENSOR_PIN3 = 9;
const int SENSOR_PIN4 = 10;
const int tc = 3;
int currentState1;  
int currentState2;
int currentState3;
int currentState4;
int x;
void setup() {
  myservo1.attach(5);
  myservo2.attach(6); 
  pinMode(SENSOR_PIN1, INPUT);
  pinMode(SENSOR_PIN2, INPUT);
  pinMode(SENSOR_PIN3, INPUT);
  pinMode(SENSOR_PIN4, INPUT);
  pinMode(tc, INPUT);
  Serial1.begin(115200);
  delay(20);
  Serial2.begin( 115200);
  delay(20);
  Serial3.begin( 115200);
  delay(20);
  sen4.begin(115200);
  delay(20);
  s1.begin( &Serial1);
  delay(20);
  s2.begin( &Serial2);
  delay(20);
  s3.begin( &Serial3);
  delay(20);
  s4.begin(&sen4);
  delay(20);
  dht.begin();
  
  
}
void drycheck()
{
 currentState1= digitalRead(SENSOR_PIN1);
 currentState2= digitalRead(SENSOR_PIN2);
 if( currentState1==1&& currentState2==1)
 {
   s1.getData(db1);
   s2.getData(db2);
   if(db1<30&&db2<30)
   {
    Serial.println("dry bin is about to fill");
    
   }
   
 }
 
}
void wetcheck()
{
 currentState3= digitalRead(SENSOR_PIN3);
 currentState4= digitalRead(SENSOR_PIN4);
 if( currentState3==1&& currentState4==1)
 {
   s3.getData(db3);
   s4.getData(db4);
   if(db3<30&&db4<30)
   {
    Serial.println("wet bin is about to fill");
   }
   
 }
}

void loop() {
  x=digitalRead(tc);
  if(x==1)
  {
  float h = dht.readHumidity();
  if(h>300)
   for (pos = 0; pos <= 145; pos += 1) {
    myservo1.write(pos);              
    delay(15);                       
  }
  else
  for (pos = 145; pos >= 0; pos -= 1) {
    myservo1.write(pos);              
    delay(15);                       
  }
  }
  drycheck();
  wetcheck();
}
void crush()
{
  currentState1= digitalRead(SENSOR_PIN1);
  currentState2= digitalRead(SENSOR_PIN2);
  currentState3= digitalRead(SENSOR_PIN3);
  currentState4= digitalRead(SENSOR_PIN4);
  s1.getData(db1);
  s2.getData(db2);
  s3.getData(db3);
  s4.getData(db4);
  if( currentState1==1&&currentState2==1&&db1<30&&db2<30)
  {
    for (pos = 0; pos <= 180; pos += 1) {
    myservo2.write(pos);              
    delay(15);                       
  }
  }
  else if( currentState3==1&&currentState4==1&&db3<30&&db4<30)
  {
    for (pos = 0; pos <= 180; pos += 1) {
    myservo2.write(pos);              
    delay(15);                       
  }
  }
}
