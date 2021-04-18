#include "ex7-1.h"
int num;
int counta, countb;
int flag = 0;
int dig0,dig1,dig2,dig3,dl;

void setup() {
  Serial.begin(9600);
  //initial display pin D2~D13
  seg7_x4_init(2); 
  randomSeed(analogRead(A0));
  Set_timer();
}

void Set_timer(){
  TCCR2A = 0; //set entire TCCR2A reg to 0
  TCCR2B = 0; //same for TCCR2B
  TCNT2 = 0;  //initialize counter to 0
  TCCR2A = TCCR2A | (1<<WGM02); // turn on CTC mode (21)
  
  // 0.001sec x 16M/prescaler:256 => TOP = 62.5
  TCCR2B = TCCR2B | (1<<CS12);   //(22)
  OCR2A = 62.5;
  TIMSK2 = TIMSK2 | (1<<OCIE2A); // enable timer compare interrupt
}

void loop() {
  if(Serial.available()){
    num = random(0,10000);
    Serial.println(num);
    Serial.read();
    counta=0;
    flag = 1;
  }
}

ISR(TIMER2_COMPA_vect){
  // every interrupt counts will +1，
  // when counts=3000(each interrupt cost 0.001sec，3000=3sec) print random number 
  counta++;
  countb++;
  if(counta == 3000){
    num = random(0,10000);
    Serial.println(num);
    Serial.read();
    counta=0;
  }
  if(countb == 10 or flag == 1){
    serial_show();
    countb = 0;
    flag = 0;
  }
}

void serial_show(){
  dl = 8;
  dig3 = num/1000;
  seg7_x4_display(3, dig3);
  delay(dl);
  dig2=(num/100)%10;
  seg7_x4_display(2,dig2);
  delay(dl);
  dig1=(num/10)%10;
  seg7_x4_display(1,dig1);
  delay(dl);
  dig0=num%10;
  seg7_x4_display(0,dig0);
  delay(dl);
  }



  
