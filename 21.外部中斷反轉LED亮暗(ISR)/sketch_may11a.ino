#define LedPin 13
#define ButtonPin 2

void setup() {
    pinMode(LedPin, OUTPUT);
    pinMode(ButtonPin, INPUT_PULLUP);
    digitalWrite(LedPin, LOW);
    // 看到|=設為1的動作/&=設為0的動作
    EIMSK |= _BV(INT0); // enable INT0
    // 將觸發模式設為CHANGE(ISC01=0,ISC00=1)
    EICRA &= ~_BV(ISC01); // EICRA= EICRA & ~_BV(ISC01)
    EICRA |= _BV(ISC00); // EICRA= EICRA | _BV(ISC00)

}

void loop() {}

void my_ISR() {
    digitalWrite(LedPin, !digitalRead(LedPin));
}

// INT0固定呼叫的中斷處理函式
ISR(INT0_vect) {
    my_ISR();
}
