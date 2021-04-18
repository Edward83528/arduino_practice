
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
   //Serial.write('Y'); //先對 TX 送出字元 Y
   mySerial.write('Y');
  //檢查 RX 緩衝器, 直到有資料進來
  while (!mySerial.available()) {} 
  if (mySerial.read()=='Y') {      
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
