const int ledPin=3; //LED輸出接腳
void setup() {
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int val ;
    for(val=0;val<256;val=val+15){  //漸亮
      analogWrite(ledPin, val);
      delay(500); //間隔0.2秒
      }
    for(val=255;val>=0;val=val-15){  //漸亮
      analogWrite(ledPin, val);
      delay(1000); //間隔0.2秒
      }

}
