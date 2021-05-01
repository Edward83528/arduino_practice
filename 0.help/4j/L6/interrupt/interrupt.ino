#define ButtonPin 2
#define LedPin 13

/*
int flag = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ButtonPin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ButtonPin),my_ISR,LOW);
}

void loop() {
  flag = 1;
  
}

void my_ISR() {
    if ( flag == 1 ) {
      Serial.println("OnClick");
    }
    flag = 0;
    Serial.println(flag);  
}

*/


int flag = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(ButtonPin,INPUT_PULLUP);
  pinMode(LedPin,OUTPUT);
  digitalWrite(LedPin,LOW);
  attachInterrupt(digitalPinToInterrupt(ButtonPin),my_ISR,FALLING);
  //EIMSK |= _BV(INTO);
  //EICRA &= ~_BV(ISC01);
  //EICRA |= _BV(ISC00);
}

void loop() {
  
}

ISR(INTO_vect){
  my_ISR();
}

void my_ISR() {
  digitalWrite(LedPin,!digitalRead(LedPin));  
}
