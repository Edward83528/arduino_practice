#include "seg7.h"

const int potPin = A0; // 可變電阻
#define Button 10 // 按鈕開關
#define LedPin 11 // LED

int RandNumber = -1; // 答案亂數初始
int buttonState = 0; // 按鈕的狀態
int buttonState_old = 0; // 上一次按鈕的狀態 比對上一個狀態的值(未按> buttonState==LOW && buttonState_old==HIGHT 按下> buttonState==HIGH && buttonState_old==LOW )
boolean ctrl = true; // 控制是否是非答案判定階段(預設true)
int flag = 0; // 控制LED亮一分鐘

long previousMillis = 0; // 上個時間點
float interval = 1000; // delay區間初始1秒

long previousMillis2 = 0; // 上個時間點
float interval2 = 500; // delay區間初始1秒

int brightness = 0; // LED亮度變數
int fadeAmount = 1; // 亮度變化變數

String str; // 存取使用者輸入

void setup() {

    // 設定Rate
    Serial.begin(9600);

    // 設定輸入(依照題目>輸入:可變電阻、按鈕開關)
    pinMode(potPin, INPUT); // 可變電阻
    pinMode(Button, INPUT_PULLUP); // 按鈕開關

    // 設定輸出(依照題目>輸出:LED、七段顯示器)
    pinMode(LedPin, OUTPUT);
    digitalWrite(LedPin, LOW); // LED
    seg7_x1_init(2); // 初始七段顯示器,第一隻接腳為D2,到D9
    seg7_x1_display(0); // 一開始顯示數字0

    randomSeed(analogRead(potPin)); // 可變電阻的值當作種子產生亂數

}

void loop() {

    if (Serial.available()) {
        str = Serial.readString(); // 讀取輸入字串
        RandNumber = str.toInt();
    }
    if (RandNumber >= 0 && RandNumber < 10) {
        unsigned long currentMillis = millis(); // 當前時間 int rnd; int val; float volt; val=analogRead(potPin); // 讀取類比可變電阻(0~1023) volt=(val * 1.906158) + 50; // 範圍限縮在(0.05s～2s>50~2000)
        interval = volt;

        buttonState = digitalRead(Button); //讀取按鍵的狀態
        //Serial.println(buttonState); // 不按:1 or 按:0

        //Serial.print("ctrl:");
        //Serial.println(ctrl);

        if (buttonState == LOW && buttonState_old == HIGH) {
            // 按下情況

            buttonState_old = buttonState;
            Serial.println("Press Button===>使用者按下按鈕\n");
            ctrl = !ctrl; // 反轉ctrl目的讓數字停止
            flag = 0; // 重置LED
            brightness = 0;
            digitalWrite(LedPin, LOW); // 點暗LED(確保LED是暗的)
        } else {

            buttonState_old = buttonState;
            Serial.println("未按下情況");
            if (ctrl == true) {
                // 平常未按下情況
                Serial.print("平常未按下情況>");
                rnd = random(0, 10); // 每次LOOP產生在0~9的亂數

                // delay(volt); // 速度由可變電阻控制
                // 不使用delay當作延遲,因為delay會讓程式中斷,中斷期間無法偵測按鈕狀態,所以用時間差代替
                if (currentMillis - previousMillis > interval) {
                    previousMillis = currentMillis;
                    seg7_x1_display(rnd); // 亂數顯示在七段
                }
                Serial.print(interval, 0); // 顯示速度
                Serial.println("ms\n");


            }
            if (ctrl == false) {
                // 進入答案判定階段(ctrl=false)
                Serial.print("判定答案階段>");
                Serial.print("正確答案:");
                Serial.print(RandNumber);
                Serial.print("亂數:");
                Serial.print(rnd);
                Serial.print("\n");
                seg7_x1_display(rnd);

                // 假如LOOP亂數和答案相同
                if (rnd == RandNumber) {

                    if (currentMillis - previousMillis2 > interval2) {
                        previousMillis2 = currentMillis;
                        Serial.println("恭喜您答對嚕!!!");
                        Serial.print("flag:");
                        Serial.print(flag);
                        Serial.print("\n");
                        // 在每次回圈brightness都會累加fadeAmount
                        if (brightness >= (RandNumber * 25.5)) {
                            flag = 1;
                        } else {
                            brightness = brightness + fadeAmount;
                        }

                        analogWrite(LedPin, brightness);
                        Serial.print("現在亮度:");
                        Serial.print(brightness);
                        Serial.print("\n");
                    }

                }
            }

        }

    }




}