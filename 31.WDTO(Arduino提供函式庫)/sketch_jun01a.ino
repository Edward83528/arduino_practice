#include <avr/wdt.h>
#define TIMEOUT WDTO_4S
#define LED_PIN 13
void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    wdt_enable(TIMEOUT); // 啟用WDT,並設定Timeout時間為4秒
    Serial.println("System Reboot ... ... ");
    Serial.println("Input char ");

}

void loop() {
    char keyin;
    if (Serial.available() > 0) {
        digitalWrite(LED_PIN, HIGH);
        keyin = Serial.read();
        if (keyin == 'x') {
            while (1);
        } else {
            delay(100);
            digitalWrite(LED_PIN, LOW);
        }
    }
    wdt_reset(); // 清除WDT的計數值,避免系統重啟
}
