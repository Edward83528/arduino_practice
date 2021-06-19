#include <avr/sleep.h>

#include <avr/power.h>

#include <avr/wdt.h>

#define LED_PIN 13
int cnt = 0;
volatile int f_wdt = 1;

ISR(WDT_vect) {
    if (f_wdt == 0) f_wdt = 1;
    else Serial.println("WDT Overrun!!!");
}

void entersleep() {
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);
    sleep_enable();
    sleep_mode();

    //*特別注意*//
    sleep_disable();
    power_all_enable();
    Serial.print("Wake up");
    Serial.println(++cnt);
    delay(100);
}


void setup() {
    Serial.begin(9600);
    Serial.println("Initialsimg...");
    delay(100);
    pinMode(LED_PIN, OUTPUT);

    MCUSR &= ~(1 << WDRF);

    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = 1 << WDP3 | 1 << WDP0;
    WDTCSR |= (1 << WDIE);
    Serial.print("Initialistion complete");
    delay(100);

}

void loop() {
    if (f_wdt == 1) {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        f_wdt = 0;
        entersleep();
    }
}
