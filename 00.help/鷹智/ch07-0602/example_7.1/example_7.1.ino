//#include <avr/sleep.h>
//#include <avr/power.h>
//#include <avr/wdt.h>

#define LED_PIN 13

/***************************************************
 * Timer1的COMPA中斷服務程式，每1秒產生一次中斷
 ***************************************************/
ISR(TIMER1_COMPA_vect)
{
   digitalWrite(LED_PIN,!digitalRead(LED_PIN));  //反轉LED現在的狀態
}

/***************************************************
 * 設定定時器
 ***************************************************/
void SetupTimer(void)
{
   //---step1:初始暫存器
   TCCR1A=0;
   TCCR1B=0;
   TCNT1=0;

   //---step2:設定CTC模式
   TCCR1B = TCCR1B | (1<<WGM12);  //將1左移3個位元，進行位元OR邏輯運算

   //---step3:設定預先除頻倍數prescaler與正確的TOP上限值
   //在prescaler=256，TOP=62500的設定下，會固定每一秒產生一次中斷
   TCCR1B = TCCR1B | (1<<CS12);   //prescaler=256
   OCR1A  = 62500;                //設定TOP=62500

   //---step4:致能對應的中斷
   TIMSK1 = TIMSK1 | (1<<OCIE1A); //致能輸出比較中斷A
}

/***************************************************
 * setup
 ***************************************************/
void setup()
{
   Serial.begin(9600);
   pinMode(LED_PIN,OUTPUT);
   digitalWrite(LED_PIN, HIGH);
   SetupTimer();  //設定定時器
}

/***************************************************
 * loop
 ***************************************************/
void loop()
{
int i;
   for(i=0;i<=100;i++) 
   Serial.println(i);
   }
