const int potPin=A0;

void setup() {
  pinMode(potPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  int val;
  float volt;
  val=analogRead(potPin);
  volt=val*0.00488;
  Serial.print(volt,1);
  Serial.println('v');
  delay(1000);

}
