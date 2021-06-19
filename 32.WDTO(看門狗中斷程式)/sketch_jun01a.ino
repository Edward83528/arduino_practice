#include <avr/wdt.h>
#define LED_PIN 13
volatile int flag = 0;

ISR(WDT_vect) {
    Serial.println("Timeout, no reboot");
    digitalWrite(LED_PIN, LOW);
    flag = 0;
}

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);

    MCUSR &= ~(1 << WDRF);
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = 1 << WDP3 | 1 << WDP0;
    WDTCSR |= (1 << WDIE);
    Serial.println("System Reboot ..... ");
    Serial.println("Input char");

}

void loop() {
    char Keyin;

    if (Serial.available() > 0) {
        digitalWrite(LED_PIN, HIGH);
        Keyin = Serial.read();
        if (Keyin == 'x') {
            flag = 1;
            while (flag);
        } else {
            delay(100);
            digitalWrite(LED_PIN, LOW);
        }

    }
    asm("WDR");
}
