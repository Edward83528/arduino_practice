/*** 傾斜/滾珠開關範例 ***/
#define Ball 2  //指定滾珠開關的接腳為D2
#define Led 13  //指定LED的接腳為D13

void setup() {
  pinMode(Ball,INPUT_PULLUP); //設定滾珠開關接腳，並啟用內建的上拉電阻
  pinMode(Led,OUTPUT);       //設定LED接腳為輸出模式
}

void loop() {
  if(digitalRead(Ball)==LOW)   //讀取滾珠開關接腳的電位是否為LOW
    digitalWrite(Led,HIGH);    //若是，點亮LED
  else digitalWrite(Led,LOW);  //否則關閉LED
}
