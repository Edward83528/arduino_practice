#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#define LED_PIN 9
int mDc = 5 ;
volatile int f_wdt=1;
int mStep = 0;

unsigned int toggle = 0;  
unsigned int count = 0;  
unsigned int fcount = 0;
unsigned int isL = 1;

/// For Prescaler == 64
///  1 秒 / (16 000 000 / 64) = 1/250000 =  0.000004 sec / per cycle
/// 0.1 sec / 0.000004 sec -1 = 25000 -1 = 24999
/// 0.0001 sec / 0.000004 sec -1 = 25 -1 = 24
const int myTOP = 24;  // 0.0001 sec when Prescaler == 64

void InitMyTimerOne()
{
  TCCR1A = 0;
  TCCR1B = (1<<WGM12);  // CTC mode; Clear Timer on Compare
  TCCR1B |= (1<<CS10) | (1<<CS11);  // Prescaler == 64
  OCR1A = myTOP;  // TOP count for CTC, 與 prescaler 有關
  TCNT1=0;  // counter 歸零 
  TIMSK1 |= (1 << OCIE1A);  // enable CTC for TIMER1_COMPA_vect
}


void InitWDT()
{
  /*** Setup the WDT ***/
  /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF);  //將MCUSR暫存器中的WDRF位元清空為0
  //我們必須先將WDTCSR暫存器中的WDCE位元設為1，
  //才可以改變WDE或prescaler的設定值。
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = 1<<WDP3 ; //設定WDP[3:0]=1000，timeout時間為4秒  
  WDTCSR |= (1<<WDIE);  //設定WDT的執行模式為中斷模式
  PrintMsg("Initialisation complete."); 
}

void PrintMsg(String val) {
  Serial.println(val); 
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  randomSeed(analogRead(A0));

  pinMode(LED_PIN,OUTPUT);

  InitWDT();
  InitMyTimerOne();

}

void loop() {

  if(f_wdt == 1) {
    if ( mStep == 0 )
    {
      isL = 0;
      digitalWrite(LED_PIN,LOW);
      // 產生亂數
      Serial.println("Step:0");
      mDc = random(5,95);
      Serial.print("RandomNumber:"); Serial.println(mDc); 
      delay(100);
    }
    if( mStep == 1 )
    {
      isL = 1;
      Serial.println("Step:1 - Light LED");
      delay(100);

    }
    f_wdt = 0;
    enterSleep();  //進入睡眠模式
  }
}

void enterSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);  //設定power-save睡眠模式
  sleep_enable(); //開啟睡眠功能
  sleep_mode();   //進入睡眠狀態
  
  /* 特別注意，此為喚醒後的程式執行點 */
  sleep_disable();    //關閉睡眠功能
  power_all_enable(); //致能所有的周邊
}

ISR(WDT_vect) {
  if(f_wdt == 0) 
    f_wdt=1;
    if ( mStep == 0 )
    {
         mStep = 1;
    }
    else
    {
        mStep = 0;
    }
}

ISR(TIMER1_COMPA_vect) {
  // 0.1ms 發生中斷
  if( isL == 1) {
    digitalWrite(LED_PIN,HIGH);
    
    count++;    
    if( count < mDc ){
      digitalWrite(LED_PIN,HIGH);
    }
    if(count > mDc){
        digitalWrite(LED_PIN,LOW);
    }
    if(count > 100){
        count = 0;
    }
    
  }
}
