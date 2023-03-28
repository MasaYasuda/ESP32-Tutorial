#include <Arduino.h>
#include <PS4Controller.h>

void setup()
{

  Serial.begin(115200);
  PS4.begin("xx:xx:xx:xx:xx:xx");
  Serial.println("Ready.");
  pinMode(5, OUTPUT);
}

void loop()
{
  // Below has all accessible outputs from the controller
  if (PS4.isConnected())
  {
    if (PS4.Circle())
    {
      Serial.println("Circle Button");
      digitalWrite(5, HIGH);
    }
    else
    {
      digitalWrite(5,LOW);
    }
    Serial.println();
    // This delay is to make the output more human readable
    // Remove it when you're not trying to see the output

    delay(10);
  }
}