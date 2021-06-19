#define LedPin 13
#define ButtonPin 2
int flag = 1;
void setup() {
    pinMode(LedPin, OUTPUT);
    pinMode(ButtonPin, INPUT_PULLUP);
    digitalWrite(LedPin, LOW);

}

void loop() {
    if (digitalRead(ButtonPin) == HIGH) {
        flag = 1;

    }
    if (digitalRead(ButtonPin) == LOW && flag == 1) {
        digitalWrite(LedPin, !digitalRead(LedPin)); // 反轉LED燈狀態
        flag = 0;
    }

}
