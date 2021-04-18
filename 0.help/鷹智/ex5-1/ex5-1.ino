#define pin 13
void setup() {
  pinMode(pin,OUTPUT);

}

void loop() {
  tone(pin,31,2000);
  delay(3000);//延遲3s

}
