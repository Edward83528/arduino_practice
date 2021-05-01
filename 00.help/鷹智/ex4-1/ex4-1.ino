void setup() {
 pinMode(13, OUTPUT); //設定數位接腳13為OUTPUT模式

}

void loop() {
 digitalWrite(13, HIGH); //將HIGH寫到(輸出)接腳13
 delay(1000); //延遲1秒
 digitalWrite(13, LOW); //將LOW寫到(輸出)接腳13
 delay(1000); //延遲1秒
 

}
