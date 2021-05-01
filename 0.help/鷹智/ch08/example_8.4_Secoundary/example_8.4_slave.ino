#include <Wire.h>
int flag=0, cnt=0;
//***************************************************
void setup() {
  pinMode(13,OUTPUT);            //設定內建LED(D13)接腳為輸出模式
  Wire.begin(8);                 //將本裝置初始成slave，且位址為8
  Wire.onReceive(receiveEvent);  //註冊onReceive要執行的函式
  Wire.onRequest(requestEvent);  //註冊onRequest要執行的函式
}

//***************************************************
void loop() {
  if(flag==1) {                  //flag為1表示從master接收到資料
    digitalWrite(13,HIGH); delay(1000-cnt*100);
    digitalWrite(13,LOW);
    cnt++;  flag=0;
  }
}

//***************************************************
void receiveEvent(int bytes) {
  while(!Wire.available());
  cnt=Wire.read();
  flag=1;
}

//***************************************************
void requestEvent( ) {
  Wire.write(cnt);
}
