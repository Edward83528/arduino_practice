#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#define LED_PIN 13

int cnt = 0;
int count; //放入中斷時的數字
volatile int f_wdt=1;

ISR(WDT_vect){
  if(f_wdt == 0){
    f_wdt=1;
    Serial.println("Sleeping..");
    delay(200);
  }
   
}
 
void enterSleep(){     //進入睡眠模式 
  for(int a = count; a<100; a++){
    if(f_wdt == 0){
      if(a == 99){
        a = 0;
      }
      Serial.println(a);
      delay(200);
      count = a;
    }
  }
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);//設定POWER-SAVE睡眠模式
  sleep_enable();//進入睡眠模式 
  sleep_mode();//進入睡眠狀態

 /* 特別注意，此為喚醒後的程式執行點 */
  sleep_disable();
  power_all_enable();
  Serial.print("Wake up: ");  Serial.println(++cnt);
  delay(100);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initialising..."); delay(100);
  pinMode(LED_PIN,OUTPUT);
  /*** Setup the WDT ***/
  /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF); //將MCUSR暫存器中的WDRF位元清空為0
                       
                       
  WDTCSR |= (1<<WDCE) | (1<<WDE); //先將WDTCSR暫存器中的WDCE位元設為1，
                                  //才可以改變WDE或prescaler的設定值。
  WDTCSR = 1<<WDP3 ;  //設定WDP[3:0]=1000 wdp3=1其餘為0  timeout時間為4秒
                      //1<<WDP3 | 1<<WDP0 指wdp3=1 wdp2=0 wdp1=0 wdp0=1，WDP[3:0]=1001 timeout時間為8秒
  WDTCSR |= (1<<WDIE);  //設定WDT的執行模式為中斷模式
}

void loop() {
  if(f_wdt == 1){
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); //反轉LED現在的狀態
    
    f_wdt = 0;
    
    enterSleep();//進入睡眠模式
  }
}
