#include "seg7.h"

const int potPin = A0;

void setup() {
    pinMode(potPin, INPUT);
    Serial.begin(9600);
    seg7_x1_init(2); // 初始七段顯示器,第一隻接腳為D2,到D9
    seg7_x1_display(0); // 一開始顯示數字0
}

void loop() {
    int val;
    float volt;
    int i;
    for (int i = 2; i <= 7; i++) {
        val = analogRead(potPin);
        volt = val * 0.00488 * 400; // 控制在0到2秒間
        Serial.println(volt, 1);

        digitalWrite(i, HIGH);
        delay(volt);
        digitalWrite(i, LOW);
    }

}