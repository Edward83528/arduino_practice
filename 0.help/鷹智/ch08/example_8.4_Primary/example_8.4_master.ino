#include <Wire.h>
int cnt=0;
//***************************************************
void setup() {
  pinMode(13,OUTPUT);        //設定內建LED(D13)接腳為輸出模式
  Wire.begin();              //將本裝置初始成master
}

//***************************************************
void loop() {
  if(cnt==10) cnt=0;
  digitalWrite(13,HIGH); delay(1000-cnt*100);  //點亮LED一段時間後熄滅
  digitalWrite(13,LOW);
  Wire.beginTransmission(8);      //向slave #8 傳送資料
  Wire.write(cnt);                //傳送cnt的值
  if(Wire.endTransmission()==0) { //傳送成功
    while(1) {
      Wire.requestFrom(8,1);      //向slave #8請求1 byte資料
      while(!Wire.available());
      if(Wire.read()==(cnt+1))    //如果slave回傳的值等於cnt+1
      { cnt++; break; }           //cnt=cnt+1，並跳出等待迴圈
    } 
  }
}
