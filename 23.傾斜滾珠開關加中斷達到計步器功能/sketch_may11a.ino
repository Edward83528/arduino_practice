#define Ball 2
#define LedPin 13
int flag = 1;
int step_num = 0;
void setup() {

    // 設定Rate
    Serial.begin(9600);

    pinMode(Ball, INPUT_PULLUP);
    pinMode(LedPin, OUTPUT);

    // 看到|=設為1的動作/&=設為0的動作
    EIMSK |= _BV(INT0); // enable INT0
    // 將觸發模式設為CHANGE(ISC01=0,ISC00=1)
    EICRA &= ~_BV(ISC01); // EICRA= EICRA & ~_BV(ISC01)
    EICRA |= _BV(ISC00); // EICRA= EICRA | _BV(ISC00)

}

void loop() {
    if (flag == 1) {
        Serial.println(step_num);
        flag = 0;
    }
}

void my_ISR() {
    if (digitalRead(Ball) == LOW) {
        digitalWrite(LedPin, HIGH);
        flag = 1;
        step_num++;
    } else {
        digitalWrite(LedPin, LOW);
    }
    delay(1000);
}

// INT0固定呼叫的中斷處理函式
ISR(INT0_vect) {
    my_ISR();
}
