#include "seg7.h"

void setup() {
    seg7_x1_init(2); // 初始七段顯示器,第一隻接腳為D2,到D9
    seg7_x1_display(0); // 一開始顯示數字0
}

void loop() {
    int i;
    for (int i = 0; i < 10; i++) {
        seg7_x1_display(i);
        delay(1000);
    }

}