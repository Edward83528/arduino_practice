#include <SoftwareSerial.h>
int LED=13;
//建立軟體串列埠腳位 (RX, TX)
SoftwareSerial mySerial(11,10);

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  //檢查 RX 緩衝區, 直到有資料進來
  while (!mySerial.available()) {} 
  if (mySerial.read()=='Y') {      
  //若收到字元 Y, LED 閃兩下
    led_blink();
    led_blink();
  } 
  mySerial.write('Y'); //在 TX 送出字元 Y 給對方
}

void led_blink() {
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(500);
}
