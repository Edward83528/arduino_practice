const int potPin = A0;
const int ledPin = 3;


void setup() {
    Serial.begin(9600);
    pinMode(potPin, INPUT);
    pinMode(ledPin, OUTPUT);
    
}

void loop() {
    int val;
    float volt;
    val = analogRead(potPin); // 0~1023
    volt = val * 0.2492; // 0~254.93

    analogWrite(ledPin, volt); // analogWrite value 要 在限制0~255

    Serial.println(volt); // 印出value

    delay(100);

}