//LED燈的亮度控制
const int ledPin=3; //LED輸出的接角
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int val ;            
    for(val=0;val<256;val=val+15){ //漸亮
      analogWrite(ledPin, val);
      delay(100); //間隔0.2秒
    }
  for(val=255;val>=0;val=val-15){ //漸暗
    analogWrite(ledPin, val);
    delay(100); //間隔0.2秒
  }
}
