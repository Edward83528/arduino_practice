
#include "ex7-1.h"
int num;
void setup() {
  Serial.begin(9600);
  seg7_x4_init(2);
  randomSeed(analogRead(A0));//類比輸入讀取0-1023
  num=random(0,10000);
}

ISR(TIMER2_COMPA_vect)
{
   cnt i++
   if(cnt_A >4 ){
    val
     myjobOne();
    }
   if(cnt_B == 3000){
    myjobTwo();
    }
 }

void loop() {
int dig0,dig1,dig2,dig3;

  if(Serial.available()) { num=random(0,10000); Serial.println(num); Serial.read(); } //0-9999
  dig3=num/1000;
  seg7_x4_display(3,dig3);
  delay(2);
  dig2=(num/100)%10;
  seg7_x4_display(2,dig2);
  delay(2);
  dig1=(num/10)%10;
  seg7_x4_display(1,dig1);
  delay(2);
  dig0=num%10;
  seg7_x4_display(0,dig0);
  delay(2);
}
void myJobOne( ) {
    digitalDispaly 
  //digitalWrite(ledPin, ggyy);  // ggyy 是 0 或 1
  ggyy = 1 - ggyy; //  給下次進入 用
}
void myJobTwo( ) {
  digitalWrite(led8, ! digitalRead(led8));  // Toggle led8
}

void setMyTimer2( ){
  cli();  // 禁止中斷
  TCCR2A = bbs(WGM21);  // CTC mode 2; Clear Timer on Compare, see p.158-162
  TCCR2B = bbs(CS22);  // Prescaler == 64; see p.162 in datasheet 
  ///// 注意 WGM22 在 TCCR2B, 但 WGM21 與 WGM20 在 TCCR2A; 
  ///// mode 由 WGM22, WGM21, WGM20 決定 (see datasheet p.158-162)
  OCR2A = myTOP;  // TOP count for CTC, 與 prescaler 有關
  TCNT2=0;  // counter 歸零 
  TIMSK2 |= bbs(OCIE2A);  // enable CTC for TIMER2_COMPA_vect
  sei();  // 允許中斷
}
