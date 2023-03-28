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
const int led;

// プロトタイプ宣言
void output(int pinA, int pinB, int pinPWM, int order);

// 起動時実行関数
void setup()
{
  // GPIOピン出力設定
  //  1（第1象限のモータ用）
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

  // LED用
  pinMode(led, OUTPUT);

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

    if (PS4.Circle() != 0) // コマンド受付フェーズに遷移
    {
      delay(10); // バウンス（チャタリング）防止
      digitalWrite(led, HIGH);
      while (PS4.Circle() != 0)
      {
      } // 〇ボタン離すまで待つ
      delay(10);

      // コマンド受付フェーズ
      int buffer[10];
      int count = 0;
      unsigned long start_time = millis();
      while (millis() - start_time < 5000) // 5秒間のタイムアウト設定
      {
        int input = 1 * PS4.Up() + 2 * PS4.Right() + 3 * PS4.Down() + 4 * PS4.Left() + 5 * PS4.R1() + 6 * PS4.L1() + 7 * PS4.Circle();
        if (input != 0) // 入力があったら
        {
          delay(10);
          if (input == 7)
            break;
          else
          {
            buffer[count] = input;

            while (1) // 離れるまで待つ
            {
              int tmp = 1 * PS4.Up() + 2 * PS4.Right() + 3 * PS4.Down() + 4 * PS4.Left() + 5 * PS4.R1() + 6 * PS4.L1() + 7 * PS4.Circle();
              if (tmp == 0)
                break;
            }
            delay(10);
            count++;
          }
        }
      }
      digitalWrite(led, LOW);

      // 移動フェーズ
      for (int i = 0; i < count; i++)
      {
        if (buffer[i] == 1)
        {
          Serial.println("前進");
          output(p1A, p1B, p1PWM, 2);
          output(p2A, p2B, p2PWM, 1);
          output(p3A, p3B, p3PWM, 1);
          output(p4A, p4B, p4PWM, 2);
        }
        else if (buffer[i] == 2)
        {
          Serial.println("右移動");
          output(p1A, p1B, p1PWM, 1);
          output(p2A, p2B, p2PWM, 1);
          output(p3A, p3B, p3PWM, 2);
          output(p4A, p4B, p4PWM, 2);
        }
        else if (buffer[i] == 3)
        {
          Serial.println("後退");
          output(p1A, p1B, p1PWM, 1);
          output(p2A, p2B, p2PWM, 2);
          output(p3A, p3B, p3PWM, 2);
          output(p4A, p4B, p4PWM, 1);
        }
        else if (buffer[i] == 4)
        {
          Serial.println("左移動");
          output(p1A, p1B, p1PWM, 2);
          output(p2A, p2B, p2PWM, 2);
          output(p3A, p3B, p3PWM, 1);
          output(p4A, p4B, p4PWM, 1);
        }
        else if (buffer[i] == 5)
        {
          Serial.println("時計回り");
          output(p1A, p1B, p1PWM, 1);
          output(p2A, p2B, p2PWM, 1);
          output(p3A, p3B, p3PWM, 1);
          output(p4A, p4B, p4PWM, 1);
        }
        else if (buffer[i] == 6)
        {
          Serial.println("反時計回り");
          output(p1A, p1B, p1PWM, 2);
          output(p2A, p2B, p2PWM, 2);
          output(p3A, p3B, p3PWM, 2);
          output(p4A, p4B, p4PWM, 2);
        }
        else
        {
          Serial.println("緊急停止");
          output(p1A, p1B, p1PWM, 0);
          output(p2A, p2B, p2PWM, 0);
          output(p3A, p3B, p3PWM, 0);
          output(p4A, p4B, p4PWM, 0);
          return;
        }
      }
    }
  }
}
