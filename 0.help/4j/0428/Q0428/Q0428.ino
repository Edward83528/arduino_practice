#define pin 13

void setup() {
  // put your setup code here, to run once:
  pinMode(pin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(pin,31);
  delay(2000);
  noTone(pin);
  delay(2000);
}
