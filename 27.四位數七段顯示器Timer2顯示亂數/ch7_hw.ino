#include "seg7.h"

int dig0, dig1, dig2, dig3, dl;
int num;
int count;
int flag = 0;

void setup() {
	// 使用四位數的七段顯示器來顯示0000~9999的亂數，當PC端輸入任一按鍵後，就換下一組亂數，數字不能閃爍。
	// 由pin 2 到 pin 13，對應到 a, b, c, d, e, f, g, h, 0, 1, 2, 3
    Serial.begin(9600);

    seg7_x4_init(2); // 初始化接腳(D2~D13)

    randomSeed(analogRead(A0));
    num = random(0, 10000); // 設定0~9999亂數

    setTimer(); // 設定計時器 

}

void loop() {
    show();
}

void setTimer(void) {

    TCCR2A = 0; // 初始化TCCR2A=0
    TCCR2B = 0; // 初始化TCCRB=0
    TCNT2 = 0; // 初始化計數器TCNT2=0
    TCCR2A = TCCR2A | (1 << WGM02); // 切換成CTC Mode
    // WGM02=3(定義在time.h)
    TCCR2B = TCCR2B | (1 << CS12); // Prescaler=256
    // CS12(定義在time.h)

    OCR2A = 62.5; // 設定Top=62.5,加速中斷時間

    TIMSK2 = TIMSK2 | (1 << OCIE2A); // 智能輸出比較中斷A

}

ISR(TIMER2_COMPA_vect) {
    if (Serial.available()) {
        num = random(0, 10000);
        Serial.println(num);
        Serial.read();
        show();
    }
}

void show() {

    dl = 5;

    dig3 = num / 1000;
    seg7_x4_display(3, dig3);
    delay(dl);
    dig2 = (num / 100) % 10;
    seg7_x4_display(2, dig2);
    delay(dl);
    dig1 = (num / 10) % 10;
    seg7_x4_display(1, dig1);
    delay(dl);
    dig0 = num % 10;
    seg7_x4_display(0, dig0);
    delay(dl);

}
