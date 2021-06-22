#include <avr/sleep.h>

#include <avr/power.h>

#include <avr/wdt.h>

#define LED_PIN 13 // LED亮的接腳

int stepNow = 0; // 紀錄現在是第幾步驟
volatile int WDT_flag = 1;
int dutyCycle = 25; // 存放產生的亂數並當作步驟1的duty cycle
int LEDLight = 0; // 是否點亮LED
int cnt = 0;
unsigned int count = 0;

const int top = 24;
void init_Timer1() {

    TCCR1A = 0;
    TCCR1B = (1 << WGM12); // CTC mode; Clear Timer on Compare
    TCCR1B |= (1 << CS10) | (1 << CS11); // Prescaler == 64
    OCR1A = top; // TOP count for CTC, 與 prescaler 有關
    TCNT1 = 0; // counter 歸零 
    TIMSK1 |= (1 << OCIE1A); // enable CTC for TIMER1_COMPA_vect

    Serial.println("initializing Timer");
    delay(100);
}

void init_WDT() {

    MCUSR &= ~(1 << WDRF);
    //我們必須先將WDTCSR暫存器中的WDCE位元設為1，才可以改變WDE或prescaler的設定值。
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = 1 << WDP3; // 設定WDP[3:0]=1000，timeout時間為4秒  
    WDTCSR |= (1 << WDIE); // 設定WDT的執行模式為中斷模式

    Serial.println("initializing WDT");
    delay(100);

}

void setup() {

    Serial.begin(9600);

    randomSeed(analogRead(A0)); // 給亂數種子

    pinMode(LED_PIN, OUTPUT);

    init_WDT();

    init_Timer1();

}
void loop() {
    step0();
    step1();
}

// 自動產生並印出x=2~50的亂數(duty cycle),接著進入省電模式(power-save)4秒鐘
void step0() {
    if (WDT_flag == 1) {
        if (stepNow == 0) {
            Serial.println("========== step-0");
            digitalWrite(LED_PIN, LOW); // 先確定LED為暗
            LEDLight = 0; // 不點亮LED
            dutyCycle = random(2, 51); // 產生2~50亂數
            Serial.print("Duty cycle:");
            Serial.println(dutyCycle);
            delay(100);
            WDT_flag = 0; // 跳出無窮迴圈
            Serial.println("sleep");
            delay(100);
            enterSleep(); // 進入睡眠模式
        }
    }
}
// 使用Timer1模擬PWM頻率100HZ,duty cycle=x亂數%,在pin13持續點亮LED 4秒鐘後關閉回到step0
void step1() {
    if (WDT_flag == 1) {
        if (stepNow == 1) {
            Serial.println("========== step-1");
            LEDLight = 1; // 讓LED亮
            delay(100);
        }
        Serial.println("PWM ...");
        WDT_flag = 0; // 跳出無窮迴圈
    }
}
void enterSleep() {
    set_sleep_mode(SLEEP_MODE_PWR_SAVE); // 設定power-save睡眠模式
    sleep_enable(); //開啟睡眠功能
    sleep_mode(); //進入睡眠狀態

    sleep_disable(); // 關閉睡眠功能
    power_all_enable(); // 致能所有的周邊

}
ISR(WDT_vect) {
    // 看門狗時間到喚醒
    if (WDT_flag == 0) {
        Serial.println("Wake up >>> ");
        WDT_flag = 1;
    }
    if (stepNow == 0) {
        // 喚醒後如果目前是step0要換到step1的功能
        stepNow = 1;
    } else {
        // 反之目前是step1要換到step0的功能
        stepNow = 0;
    }
}

ISR(TIMER1_COMPA_vect) {
    if (LEDLight == 1) {
        digitalWrite(LED_PIN, HIGH);
        count++;
        if (count < dutyCycle) {
            digitalWrite(LED_PIN, HIGH);
        }
        if (count > dutyCycle) {
            digitalWrite(LED_PIN, LOW);
        }
        if (count > 100) {
            count = 0;
        }
    }
}
