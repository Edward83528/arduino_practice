
int LED=13;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.write('Y'); //先對 TX 送出字元 Y
  //檢查 RX 緩衝器, 直到有資料進來
  while (!Serial.available()) {} 
  if (Serial.read()=='Y') {      
  //若收到 Y, LED 閃兩下
    led_blink();
    led_blink();
  }
}

void led_blink() {
  digitalWrite(LED, HIGH);
  delay(3000);
  digitalWrite(LED, LOW);
  delay(1000);
}
