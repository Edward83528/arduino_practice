#define LedPin 13 //Uno開發版上內建LED的接腳固定為D13
#define ButtonPin 2 //指定按鈕開關的接腳為D2
void setup() {
  pinMode(LedPin, OUTPUT);           //設定lde接腳為輸出模式
  pinMode(ButtonPin, INPUT_PULLUP);  //設定button接腳，並啟用內建的上拉電阻
  digitalWrite(LedPin,LOW);          //初始led為熄滅的狀態

}

void loop() {
  if(digitalRead(ButtonPin)!= LOW) //讀取Button接腳的店為使否為Low
    digitalWrite(LedPin, HIGH);    //若是就代表按下開關，開啟LED
  else 
    digitalWrite(LedPin, LOW);    // 否則關閉LED

}
