#include <avr/wdt.h>

volatile int flag = 0;

int num;
int tempNum = 0;

void setup() {
    Serial.begin(9600);
    pinMode(2, OUTPUT);
    num = random(1, 21); // 設定1~20亂數
    setTimer(); // 設定計時器 

    MCUSR &= ~(1 << WDRF);
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = 1 << WDP3 | 1 << WDP0;
    WDTCSR |= (1 << WDIE);
    Serial.println("System Reboot ..... ");

}
ISR(WDT_vect) {
    Serial.println("Timeout, no reboot");
    digitalWrite(2, LOW);
    flag = 0;
}
ISR(TIMER2_COMPA_vect) {
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

void loop() {

    num = random(1, 21); // 設定1~20亂數
    Serial.println(num);
    if (num == 19) {
        flag = 1;
        digitalWrite(2, HIGH);
        while (flag);
    } else {
        delay(100);
        digitalWrite(2, LOW);
    }
    asm("WDR");

}
void show() {

}
