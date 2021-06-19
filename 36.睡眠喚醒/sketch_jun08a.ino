#include <avr/sleep.h>

#include <avr/wdt.h>

#define LedPin 13
#define ButtonPin 2

int WUP_cnt = 0, num = 0;
volatile int WDT_cnt = 0, WDT_flag = 0;

int state = 0;

void enterSleep() {
    Serial.println("Sleeping ...");
    delay(100);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    Serial.print("Wake up");
    Serial.println(WUP_cnt++);
    delay(100);
}


void setup() {

    Serial.begin(9600);
    Serial.println("Initialsimg...");
    delay(100);

    pinMode(LedPin, OUTPUT);
    pinMode(ButtonPin, INPUT_PULLUP);
    digitalWrite(LedPin, LOW);
    // 看到|=設為1的動作/&=設為0的動作
    EIMSK |= _BV(INT0); // enable INT0
    // 將觸發模式設為CHANGE(ISC01=0,ISC00=1)
    EICRA &= ~_BV(ISC01); // EICRA= EICRA & ~_BV(ISC01)
    EICRA |= _BV(ISC00); // EICRA= EICRA | _BV(ISC00)

}

void loop() {

    if (state) {
        delay(2000);
        state = LOW;
        digitalWrite(LedPin, state);
        enterSleep();
    }
    delay(200);

}

void my_ISR() {
    digitalWrite(LedPin, !digitalRead(LedPin));
}

ISR(INT0_vect) {
    my_ISR();
    if (state == 0) state = 1;
    else Serial.println("OverRun!!!");
    WDT_cnt++;
}
