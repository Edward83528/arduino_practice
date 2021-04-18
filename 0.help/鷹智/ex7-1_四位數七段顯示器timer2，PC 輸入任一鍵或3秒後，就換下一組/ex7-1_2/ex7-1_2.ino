#include "ex7-1.h"
int num;
int count =0;

void timer2(){
  TCCR2A = 0; //set entire TCCR2A reg to 0
  TCCR2B = 0; //same for TCCR2B
  TCNT2 = 0;  //initialize counter to 0
  TCCR2A = TCCR2A | (1<<WGM02); // turn on CTC mode (21)
  
  // 0.001sec x 16M/prescaler:256 => TOP = 62.5
  TCCR2B = TCCR2B | (1<<CS12);   //(22)
  OCR2A = 62.5;// = (16*10^6) / (8000*8) - 1 (must be <256)
  TIMSK2 = TIMSK2 | (1<<OCIE2A); // enable timer compare interrupt
}

void setup() {
  Serial.begin(9600);
  seg7_x4_init(2);
  randomSeed(analogRead(A0));//類比輸入讀取0-1023
  //num=random(0,10000);
  timer2();
}

void loop() {
  if(Serial.available()) { 
    num=random(0,10000); //0-9999
    Serial.println(num); 
    Serial.read(); 
    count=0;
    } 
    Seg7x4_show();
 }

ISR(TIMER2_COMPA_vect)
{
   // every interrupt counts will +1，
  // 計算count當加到 counts=3000(each interrupt cost 0.001sec，3000=3sec) print random number，在歸零
  count++;
  if(count == 3000){
    num = random(0,10000);
    Serial.println(num);
    Serial.read();
    count=0;
    Seg7x4_show();
  }
 }
void Seg7x4_show(){
  int dig0,dig1,dig2,dig3;
  dig3 = num/1000;
  seg7_x4_display(3, dig3);
  delay(3);
  dig2=(num/100)%10;
  seg7_x4_display(2,dig2);
  delay(3);
  dig1=(num/10)%10;
  seg7_x4_display(1,dig1);
  delay(3);
  dig0=num%10;
  seg7_x4_display(0,dig0);
  delay(3);
  }
