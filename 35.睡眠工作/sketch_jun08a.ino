#include <avr/sleep.h>
#include <avr/wdt.h>
int WUP_cnt=0,num=0;
volatile int WDT_cnt=0,WDT_flag=1;

ISR(WDT_vect)
{
  if(WDT_flag == 0) WDT_flag=1;
  else Serial.println("WDT Overrun!!!");
  WDT_cnt++; 
}

void enterSleep()
{
  Serial.println("Sleeping ..."); delay(100);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();

  //sleep_enable();  
  //sleep_mode();

  Serial.print("Wake up"); Serial.println(WUP_cnt++); delay(100);
}


void setup() {
  Serial.begin(9600);
  Serial.println("Initialsimg..."); delay(100);

  MCUSR &= ~(1<<WDRF);

  WDTCSR |= (1<<WDCE) | (1<<WDE);
  //WDTCSR =   1<<WDP3 | 1<<WDP0; // 8秒
  WDTCSR =   1<<WDP3; // 4秒
  WDTCSR |= (1<<WDIE);
  
  Serial.print("Initialistion complete"); delay(100);
  

}

void loop() {
    if(WDT_flag ==1)
    {
      WDT_flag = 0;
      if(WDT_cnt%2==0) enterSleep(); 
    }
    Serial.print(num++%1000); delay(100);
}
