const int potPin = A0; // 讀取可變電阻的輸入值

void setup() {
    Serial.begin(9600);
    pinMode(potPin, INPUT);
}

void loop() {
    int val;
    float volt;
    val = analogRead(potPin); // 讀取可變電阻,傳回0~1023
    //Serial.println(val);
    volt = val * 0.00488; // 轉換成電壓值5/1024=0.00488
    Serial.print(volt, 1); // 印出電壓值(取小數點1位)
    Serial.println('v');
    delay(1000);

}