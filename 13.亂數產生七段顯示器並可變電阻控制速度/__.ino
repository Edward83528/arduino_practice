#include "seg7.h"

const int potPin = A0;

void setup() {
    Serial.begin(9600);
    pinMode(potPin, INPUT);
    randomSeed(analogRead(potPin)); // 可變電阻的值當作種子產生亂數
    seg7_x1_init(2); // 初始七段顯示器,第一隻接腳為D2,到D9
    seg7_x1_display(0); // 一開始顯示數字0
}

void loop() {
    int val;
    float volt;

    int i;
    int j;
    for (int i = 0; i < 10; i++) {
        j = random(0, 10); // 產生0~9的亂數
        val = analogRead(potPin); // 0~1023
        volt = val * 2.737 + 200; // 200~3000

        Serial.println(volt, 1); // 印出延遲秒數
        seg7_x1_display(j);
        delay(volt);

    }

}