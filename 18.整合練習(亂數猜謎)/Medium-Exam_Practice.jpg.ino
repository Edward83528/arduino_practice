#include <Arduino.h>

#include <time.h>

#include "seg7.h"

#define Button 10
#define Buzzer 11
#define LedPin 12

int num = 0, flag = 0;
int RandNumber;

const int potPin = A0;
//讀取可變電阻的輸出值
bool ctrl = true;
//控制開關(預設true)

int randomNum() {
    /*RandNumber*/
    int a;
    a = rand() % 9 + 1;
    // 產生亂數
    return a;
}


void setup() {

    Serial.begin(9600);
    /**設定Rate**/

    pinMode(potPin, INPUT);
    pinMode(Button, INPUT_PULLUP);
    pinMode(Buzzer, OUTPUT);

    seg7_x1_init(2);
    seg7_x1_display(0);

    //RandNumber=randomNum();
    RandNumber = (rand() % 9) + 1;

    digitalWrite(LedPin, LOW);

}

void loop() {

    int rnd;
    //亂數
    int val;

    float volt;

    val = analogRead(potPin);
    //val(可變電阻讀取到的數值)
    volt = (val * 1.906158) + 50;
    //範圍限縮在(0.05s～2s)

    if (digitalRead(Button) == LOW) {

        Serial.println("Press Button===>使用者按下按鈕\n");
        ctrl = !ctrl;
        delay(400);

        flag = 0;
        //重製蜂鳴器
        digitalWrite(LedPin, LOW);
    }
    if (digitalRead(Button) == HIGH && ctrl == true) {


        rnd = random(0, 9);
        seg7_x1_display(rnd);

        delay(volt);
        //Serial.print(volt,0);
        //Serial.println("ms\n");
        Serial.print(RandNumber);
        Serial.println("\n");

    }
    if (digitalRead(Button) == HIGH && ctrl == false) {

        seg7_x1_display(rnd);
        delay(1000);
        if (rnd == RandNumber) {
            digitalWrite(LedPin, HIGH);
            if (flag == 0) {
                digitalWrite(Buzzer, HIGH);
                delay(1000);
                digitalWrite(Buzzer, LOW);
                delay(1000);
                flag = 1;
            }

        }
    }
}
