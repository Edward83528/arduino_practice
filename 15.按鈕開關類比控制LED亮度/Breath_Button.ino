#define Button 10
#define Buzzer 11
#define LedPin 3

int val = 0;
bool ctrl = true;

void setup() {

    Serial.begin(9600);
    pinMode(Button, INPUT_PULLUP);
    digitalWrite(LedPin, LOW);

}

void loop() {

    if (digitalRead(Button) == LOW) {
        //當使用者按下按鈕
        if (ctrl == true) {
            val = val + 15;
            delay(300);

            if (val >= 255) {
                val = 255;
                ctrl = false;
            }

        } else if (ctrl == false) {
            val = val - 15;
            delay(300);

            if (val <= 0) {
                val = 0;
                ctrl = true;
            }

        }
    }

    Serial.print(val);
    Serial.println("ms\n");

    analogWrite(LedPin, val);
    delay(500);

}
