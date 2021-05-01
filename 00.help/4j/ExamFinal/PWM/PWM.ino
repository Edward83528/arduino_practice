
#define LED_PIN 9
unsigned int toggle = 0;  
unsigned int count = 0;  
unsigned int isL = 1;



/// For Prescaler == 64
///  1 秒 / (16 000 000 / 64) = 1/250000 =  0.000004 sec / per cycle
/// 0.1 sec / 0.000004 sec -1 = 25000 -1 = 24999
/// 0.0001 sec / 0.000004 sec -1 = 25 -1 = 24
const int myTOP = 24;  // 0.0001 sec when Prescaler == 64


ISR(TIMER1_COMPA_vect)
{
  // 0.1ms 發生中斷
  count++;     

  if( count < 50 ){
    digitalWrite(LED_PIN,HIGH);
  }

  if(count > 50){
    digitalWrite(LED_PIN,LOW);
  }

  if(count > 100){
    count = 0;
  }
}
void setup( ) {
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
  setMyTimerOne( ); 
}

void loop() {


}


void setMyTimerOne( ){
  cli();  // 禁止中斷
  TCCR1A = 0;
  TCCR1B = (1<<WGM12);  // CTC mode; Clear Timer on Compare
  TCCR1B |= (1<<CS10) | (1<<CS11);  // Prescaler == 64
  /////////
  OCR1A = myTOP;  // TOP count for CTC, 與 prescaler 有關
  TCNT1=0;  // counter 歸零 
  TIMSK1 |= (1 << OCIE1A);  // enable CTC for TIMER1_COMPA_vect
  sei();  // 允許中斷
}


/*
unsigned int toggle = 0;  
unsigned int count = 0;  
unsigned int isL = 1;

void setup()
{
  // Init 
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
  // Init Timer2
  TCCR2B = 0x00;        //Disbale Timer2 while we set it up
  TCNT2  = 130;         //Reset Timer Count to 130 out of 255
  TIFR2  = 0x00;        //Timer2 INT Flag Reg: Clear Timer Overflow Flag
  TIMSK2 = 0x01;        //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
  TCCR2A = 0x00;        //Timer2 Control Reg A: Wave Gen Mode normal
  TCCR2B = 0x05;
}

void loop()
{
  if( toggle == 1)
  {
    Serial.println(isL);
    toggle = 0;
    if( isL == 1 )
    {
      digitalWrite(LED_PIN,HIGH);
    }
    if( isL == 0 )
    {
      digitalWrite(LED_PIN,LOW);
    }
  }
}

ISR(TIMER2_OVF_vect) {
  count++;     
  // 前100亮
  if( count < 2 ){
    toggle = 1;
    isL = 1;
  }

  // 後900暗
  if(count > 2){
    toggle = 1;
    isL = 0;
  }

  if(count > 10){
    toggle = 1;
    isL = 0;
    count = 0;
  }

  TCNT2 = 130;           //Reset Timer to 130 out of 255
  TIFR2 = 0x00; 
};
*/
