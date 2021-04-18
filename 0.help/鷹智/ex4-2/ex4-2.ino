int ledPin = 13 ; 
int inPin = 7 ; 
int val = 0; //宣告int變數val來儲存digitalRead的傳回值
void setup() {
  pinMode(ledPin, OUTPUT); //設定數位接腳13為OUTPUT模式
  pinMode(inPin, INPUT_PULLUP); //設定數位接腳7為INTPUT模式，改為PULLUP避免浮接

}

void loop() {
  val = digitalRead(inPin); //讀取接腳7的訊號值，存在val
  digitalWrite(ledPin, val); //將val變數的直寫(輸出)到pin13

}
