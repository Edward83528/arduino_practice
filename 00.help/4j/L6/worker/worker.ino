#define Ball 3  //指定滾珠開關的接腳為D2

int flag = 1;
int stepNum = 0;
int continueMove1 = 0;
int continueMove2 = 0;
int f1flag = 1;
int f2flag = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Ball,INPUT_PULLUP); //設定滾珠開關接腳，並啟用內建的上拉電阻
  //attachInterrupt(digitalPinToInterrupt(Ball),my_ISR,FALLING);
  EIMSK |= _BV(INT1);
  EICRA &= ~_BV(ISC01);
  EICRA |= _BV(ISC00);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( flag == 1 ) {
      Serial.println(stepNum/100);
      flag = 0;
    }
  
}

ISR(INT1_vect){
  my_ISR();
}

void my_ISR() {
  flag = 1;
  delay(500);
  stepNum++;
}
