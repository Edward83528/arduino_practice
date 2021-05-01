#include "seg7.h"

unsigned int toggle = 0;  
unsigned int count = 0;  
int seg7num;


void setup() {
  // Init 
  Serial.begin(9600);
  seg7_x4_init(2);
  randomSeed(analogRead(A0));
  //Init Timer2
  TCCR2B = 0x00;        //Disbale Timer2 while we set it up
  TCNT2  = 130;         //Reset Timer Count to 130 out of 255
  TIFR2  = 0x00;        //Timer2 INT Flag Reg: Clear Timer Overflow Flag
  TIMSK2 = 0x01;        //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
  TCCR2A = 0x00;        //Timer2 Control Reg A: Wave Gen Mode normal
  TCCR2B = 0x05;        //Timer2 Control Reg B: Timer Prescaler set to 128
}

void loop() {
  
  if(Serial.available())
  { 
    
    seg7num=random(0,10000);
    Serial.read();
    // Reset timer2
    TIMSK2 |= (0 << OCIE1A); // deactivate timer's interrupt. 
    count = 0;
    TCNT2 = 130;
    TIFR2 = 0x00; 
    TIMSK2 |= (1 << OCIE1A); // reactivate the timer. 
  }
  
  if( toggle == 1)
  {
    seg7num=random(0,10000);  
    toggle = 0;
  }
  
  Seg7X4Show();
}

// -- Function Part --
// Timer2 interupt function.
ISR(TIMER2_OVF_vect) {
  count++;               //Increments the interrupt counter
  if(count > 2999){
    toggle = 1;
    count = 0;           //Resets the interrupt counter
  }
  TCNT2 = 130;           //Reset Timer to 130 out of 255
  TIFR2 = 0x00;          //Timer2 INT Flag Reg: Clear Timer Overflow Flag
};
// 4SizeSeg7 show function.
void Seg7X4Show()
{
  int dig0,dig1,dig2,dig3;
  dig3=seg7num/1000;
  seg7_x4_display(3,dig3);
  delay(5);
  dig2=(seg7num/100)%10;
  seg7_x4_display(2,dig2);
  delay(5);
  dig1=(seg7num/10)%10;
  seg7_x4_display(1,dig1);
  delay(5);
  dig0=seg7num%10;
  seg7_x4_display(0,dig0);
  delay(5);
}
