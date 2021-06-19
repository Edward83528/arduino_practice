#define LedPin 13
#define ButtonPin 2

void setup() {
    pinMode(LedPin, OUTPUT);
    pinMode(ButtonPin, INPUT_PULLUP);
    digitalWrite(LedPin, LOW);
    attachInterrupt(digitalPinToInterrupt(ButtonPin), my_ISR, HIGH); // HIGH高電位觸發 LOW低電位觸發 FALLING壓下去 RISING放開 CHANGE改變就觸發

}

void loop() {}

void my_ISR() {
    digitalWrite(LedPin, !digitalRead(LedPin));
}
