#include "seg7.h"

#define Button 10
int num = 0;
int flag = 0;

void setup() {
    pinMode(Button, INPUT_PULLUP);
    seg7_x1_init(2); // 初始七段顯示器,第一隻接腳為D2,到D9
    seg7_x1_display(0); // 一開始顯示數字0
}

void loop() {
    if (digitalRead(Button) == LOW) { // 假如按下開關
        //num=(num+1)%10;
        if (num >= 9) {
            num = 0;
        } else {
            num++;
        }

        flag = 1;
        delay(200);
    }
    if (flag == 1) {
        seg7_x1_display(num);
        flag = 0;
    }

}
