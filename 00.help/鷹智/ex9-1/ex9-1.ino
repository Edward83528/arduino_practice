//LED燈的亮度控制
const int ledPin=3;
void setup() {
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);

}

void loop() { //一個循環式1000us=1ms所以一次循環1000次，因此FQ是1KHZ，
              //每隔循環中有電的比率是100/100100%=10%，duty cycle占比
              //10%。模擬出5Volt*10=0.5Volt的電壓
  int val ;
    for(val=0;val<256;val=val+15){ //漸亮
      analogWrite(ledPin,val);
      delay(100); //間隔2s
      }
    for(val=255;val>=0;val=val-15){ //漸暗
      analogWrite(ledPin,val);
      delay(100); //間隔0.2s
    }
}
