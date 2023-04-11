#include <Arduino.h>
#include <PS4Controller.h>

// ピン番号の設定
const int p1A = 23;
const int p1B = 22;
const int p1PWM = 21;
const int p2A = 19;
const int p2B = 18;
const int p2PWM = 5;
const int p3A = 17;
const int p3B = 16;
const int p3PWM = 4;
const int p4A = 0;
const int p4B = 2;
const int p4PWM = 15;

// プロトタイプ宣言
void output(int pinA, int pinB, int pinPWM, int order);

// 起動時実行関数
void setup()
{
  //GPIOピン出力設定
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

  // シリアル通信の開始
  Serial.begin(115200);

  // PS4コントローラーとの接続
  PS4.begin("xx:xx:xx:xx:xx:xx");
  Serial.println("Ready.");
}

// 無限ループ関数
void loop()
{
  if (PS4.isConnected()) // PS$コントローラーが接続状態にある場合
  {
    if (PS4.Up()) // PS4コントローラーの十字上ボタンが押されている場合
    {
      Serial.println("前進");
      output(p1A, p1B, p1PWM, 2);
      output(p2A, p2B, p2PWM, 1);
      output(p3A, p3B, p3PWM, 1);
      output(p4A, p4B, p4PWM, 2);
    }
    else if (PS4.Right()) // PS4コントローラーの十字右ボタンが押されている場合
    {
      Serial.println("右移動");
      output(p1A, p1B, p1PWM, 1);
      output(p2A, p2B, p2PWM, 1);
      output(p3A, p3B, p3PWM, 2);
      output(p4A, p4B, p4PWM, 2);
    }
    else if (PS4.Down()) // PS4コントローラーの十字下ボタンが押されている場合
    {
      Serial.println("後退");
      output(p1A, p1B, p1PWM, 1);
      output(p2A, p2B, p2PWM, 2);
      output(p3A, p3B, p3PWM, 2);
      output(p4A, p4B, p4PWM, 1);
    }
    else if (PS4.Left()) // PS4コントローラーの十字左ボタンが押されている場合
    {
      Serial.println("左移動");
      output(p1A, p1B, p1PWM, 2);
      output(p2A, p2B, p2PWM, 2);
      output(p3A, p3B, p3PWM, 1);
      output(p4A, p4B, p4PWM, 1);
    }
    else if (PS4.R1()) // PS4コントローラーのR1ボタンが押されている場合
    {
      Serial.println("時計回り");
      output(p1A, p1B, p1PWM, 1);
      output(p2A, p2B, p2PWM, 1);
      output(p3A, p3B, p3PWM, 1);
      output(p4A, p4B, p4PWM, 1);
    }
    else if (PS4.L1()) // PS4コントローラーのR1ボタンが押されている場合
    {
      Serial.println("反時計回り");
      output(p1A, p1B, p1PWM, 2);
      output(p2A, p2B, p2PWM, 2);
      output(p3A, p3B, p3PWM, 2);
      output(p4A, p4B, p4PWM, 2);
    }
    else // それ以外の全ての場合（他のボタンのみ押されている、あるいは、何も押されていない場合）
    {
      Serial.println("停止");
      output(p1A, p1B, p1PWM, 0);
      output(p2A, p2B, p2PWM, 0);
      output(p3A, p3B, p3PWM, 0);
      output(p4A, p4B, p4PWM, 0);
    }
  }
  // 　ほんの少し待つ(処理速度を少し落とす)
  delay(10);
}

// モーター出力用関数
void output(int pinA, int pinB, int pinPWM, int order) // 引数：ピン番号と命令番号
{
  if (order == 1) // 命令番号が1(正回転)の場合
  {
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
    analogWrite(pinPWM, 255);
  }
  else if (order == 2) // 命令番号が2(逆回転)の場合
  {
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
    analogWrite(pinPWM, 255);
  }
  else // 命令番号がその他(例えば0)の場合
  {
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    analogWrite(pinPWM, 0);
  }
  return;
}

void output(int pin[3], int power) // 引数：ピン番号と命令番号
{
  if (power > 0) // 命令番号が1(正回転)の場合
  {
    digitalWrite(pin[0], HIGH);
    digitalWrite(pin[1], LOW);
    analogWrite(pin[2], power);
  }
  else // 命令番号がその他(例えば0)の場合
  {
    digitalWrite(pin[0], LOW);
    digitalWrite(pin[1], HIGH);
    analogWrite(pin[2], (-1) * power);
  }
  return;
}