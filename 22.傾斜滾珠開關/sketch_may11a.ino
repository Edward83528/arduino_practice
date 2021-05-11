#define Ball 2
#define LedPin 13

void setup() {
    pinMode(Ball, INPUT_PULLUP);
    pinMode(LedPin, OUTPUT);
}

void loop() {

    if (digitalRead(Ball) == LOW) {
        digitalWrite(LedPin, HIGH);
    } else {
        digitalWrite(LedPin, LOW);
    }

}
