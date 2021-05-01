const int potPin=A0;
const int ledPin=3;
void setup() {
  pinMode(potPin,INPUT);
  Serial.begin(9600);

}

void loop() {
  int val ;
  float volt;
   
  val=analogRead(potPin);
  volt=val*0.00488;
  
  int a = val/4 ; //1024/4=255顏色
  analogWrite(ledPin, a);
  
  Serial.print(val); Serial.print(" => ");
  Serial.print(volt, 1);
  Serial.println('V');
  delay(20);
  

}
