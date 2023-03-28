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
  int state = 0;

  if (PS4.isConnected())
  {
    if (PS4.Up())
    {
      Serial.println("前進");
      state = 1;
    }
    else if (PS4.Right())
    {
      Serial.println("右移動");
      state = 2;
    }
    else if (PS4.Down())
    {
      Serial.println("後退");
      state = 3;
    }
    else if (PS4.Left())
    {
      Serial.println("左移動");
      state = 4;
    }
    else if (PS4.L1())
    {
      Serial.println("時計回り");
      state = 5;
    }
    else if (PS4.R1())
    {
      Serial.println("反時計回り");
      state = 6;
    }
  }
  delay(10);
}
}
void pinSetup()
{
  // ピン出力モード設定の宣言(順：方向制御用x2 , PWM制御用)　※方向制御用は前者がHIGHの時、機体が時計回りに回転
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
  pinMode(p1A, OUTPUT);
  pinMode(p1B, OUTPUT);
  pinMode(p1PWM, OUTPUT);
  // 2（第2象限のモータ用）
  pinMode(p2A, OUTPUT);
  pinMode(p2B, OUTPUT);
  pinMode(p2PWM, OUTPUT);
  // 3（第3象限のモータ用）
  pinMode(p3A, OUTPUT);
  pinMode(p3B, OUTPUT);
  pinMode(p3PWM, OUTPUT);
  // 4（第4象限のモータ用）
  pinMode(p4A, OUTPUT);
  pinMode(p4B, OUTPUT);
  pinMode(p4PWM, OUTPUT);

  Serial.begin(115200);
}

void w1_output(int num)
{
  if (num = 0)
  {
    digitalWrite(p1A, LOW);
    digitalWrite(p1B, LOW);
    analogWrite(p1PMW, 0);
  }
  else if (num = 1)
  { // 正回転
    digitalWrite(p1A, LOW);
    digitalWrite(p1B, LOW);
    analogWrite(p1PMW, 0);
  }
}

void move_forward()
{
}
void move_back()
{
}
void move_right()
{
}
void move_left()
{
}
void rotate_right()
{
  digitalWrite(p1A, HIGH);
  digitalWrite(p1B, LOW);
  analogWrite(p1PMW, 127);
  digitalWrite(p2A, HIGH);
  digitalWrite(p2B, LOW);
  analogWrite(p2PMW, 127);
  digitalWrite(p3A, HIGH);
  digitalWrite(p3B, LOW);
  analogWrite(p3PMW, 127);
  digitalWrite(p4A, HIGH);
  digitalWrite(p4B, LOW);
  analogWrite(p4PMW, 127);
}
void rotate_right()
{
  digitalWrite(p1A, LOW);
  digitalWrite(p1B, LOW);
  analogWrite(p1PMW, 127);
  digitalWrite(p2A, LOW);
  digitalWrite(p2B, LOW);
  analogWrite(p2PMW, 127);
  digitalWrite(p3A, LOW);
  digitalWrite(p3B, LOW);
  analogWrite(p3PMW, 127);
  digitalWrite(p4A, LOW);
  digitalWrite(p4B, LOW);
  analogWrite(p4PMW, 127);
}