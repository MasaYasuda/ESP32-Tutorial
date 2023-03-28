#include <Arduino.h>

int p1A = 23;
  int p1B = 22;
  int p1PWM = 21;
  int p2A = 19;
  int p2B = 18;
  int p2PWM = 5;
  int p3A = 17;
  int p3B = 16;
  int p3PWM = 4;
  int p4A = 0;
  int p4B = 2;
  int p4PWM = 15;
  // 1（第1象限のモータ用）
  

void setup(){
  pinMode(32,OUTPUT);
pinMode(33,OUTPUT);
pinMode(25,OUTPUT);
pinMode(26,OUTPUT);
pinMode(27,OUTPUT);
pinMode(14,OUTPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
Serial.begin(115200);
}
void loop(){
  for(int i=0;i<80;i++){
    analogWrite(32,i);
    analogWrite(33,i);
    analogWrite(25,i);
    analogWrite(26,i);
    analogWrite(27,i);
    analogWrite(14,i);
    analogWrite(12,i);
    analogWrite(13,i);
    delay(1);
    Serial.println("PP");
  }
}