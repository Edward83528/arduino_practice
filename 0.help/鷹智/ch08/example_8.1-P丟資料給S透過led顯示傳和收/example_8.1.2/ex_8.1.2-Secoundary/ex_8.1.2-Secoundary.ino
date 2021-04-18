
int LED=13;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //檢查 RX 緩衝區, 直到有資料進來
  while (!Serial.available()) {} 
  if (Serial.read()=='Y') {      
  //若收到字元 Y, LED 閃兩下
    led_blink();
    led_blink();
  } 
  Serial.write('Y'); //在 TX 送出字元 Y 給對方
}

void led_blink() {
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(500);
}