#include <Arduino.h>
#include <bits/stdc++.h> //円周率M_PIの使用
#include <cmath>         //abs() for float
#include <math.h>
#include <PS4Controller.h>

// ピン番号の設定 A,B,PWM の順
const int PIN1[3] = {23, 22, 21};
const int PIN2[3] = {19, 18, 5};
const int PIN3[3] = {17, 16, 4};
const int PIN4[3] = {0, 2, 15};

// プロトタイプ宣言
void output(const int *pin, int power);

// 起動時実行関数
void setup()
{
  // GPIOピン出力設定
  for (int i = 0; i < 3; i++)
  {
    pinMode(PIN1[i], OUTPUT);
    pinMode(PIN2[i], OUTPUT);
    pinMode(PIN3[i], OUTPUT);
    pinMode(PIN4[i], OUTPUT);
  }
  // シリアル通信の開始
  Serial.begin(115200);

  // PS4コントローラーとの接続
  PS4.begin("xx:xx:xx:xx:");
  Serial.println("Ready.");
}

// 無限ループ関数
void loop()
{
  if (PS4.isConnected()) // PS$コントローラーが接続状態にある場合
  {
    // xy座標と回転量を取得
    float x = PS4.LStickX();
    float y = PS4.LStickY();
    float rot = PS4.RStickX();

    // 極座標変換
    float r = sqrt(x * x + y * y);
    float theta = atan2(y, x) * 180 / M_PI;

    // ジョイスティックのわずかな傾きは無視する
    if (r < 0.1)
      r = 0;
    if (abs(rot) < 0.1)
      rot = 0;

    if (rot != 0) // 回転命令があるとき
    {
      int power = (int)rot * 127;

      // 出力
      output(PIN1, power);
      output(PIN2, power);
      output(PIN3, power);
      output(PIN4, power);
    }
    else
    {
      // 4輪オムニホイールの運動学計算（4つの各車輪の出力値を計算する）
      int power1 = (int)r * cos((theta - 45) * M_PI / 180);
      int power2 = (int)r * cos((theta - 135) * M_PI / 180);
      int power3 = (-1) * power1;
      int power4 = (-1) * power2;

      // 出力
      output(PIN1, power1);
      output(PIN2, power2);
      output(PIN3, power3);
      output(PIN4, power4);
    }
  }
  // 　ほんの少し待つ(処理速度を少し落とす)
  delay(10);
}

void output(const int *pin, int power) // 引数：ピン番号と命令番号
{
  if (power > 0) // 命令番号が1(正回転)の場合
  {
    digitalWrite(pin[0], HIGH);
    digitalWrite(pin[1], LOW);
    analogWrite(pin[2], power*60);
  }
  else // 命令番号がその他(例えば0)の場合
  {
    digitalWrite(pin[0], LOW);
    digitalWrite(pin[1], HIGH);
    analogWrite(pin[2], (-1) * power*60);
  }
  return;
}