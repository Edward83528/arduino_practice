#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#define LED_PIN 13
int cnt=0;
volatile int f_wdt=1;

/***************************************************
 * 看門狗中斷服務程式 
 ***************************************************/
ISR(WDT_vect) {
  if(f_wdt == 0) f_wdt=1;
  else Serial.println("WDT Overrun!!!");
}

/***************************************************
 * 進入睡眠模式
 ***************************************************/
void enterSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);  //設定power-save睡眠模式
  sleep_enable(); //開啟睡眠功能
  sleep_mode();   //進入睡眠狀態
  
  /* 特別注意，此為喚醒後的程式執行點 */
  sleep_disable();    //關閉睡眠功能
  power_all_enable(); //致能所有的周邊
  Serial.print("Wake up: "); Serial.println(++cnt);
  delay(100);
}

/***************************************************
 * setup
 ***************************************************/
void setup() {
  Serial.begin(9600);
  Serial.println("Initialising..."); delay(100);
  pinMode(LED_PIN,OUTPUT);

  /*** Setup the WDT ***/
  /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF);  //將MCUSR暫存器中的WDRF位元清空為0
  //我們必須先將WDTCSR暫存器中的WDCE位元設為1，
  //才可以改變WDE或prescaler的設定值。
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = 1<<WDP3 | 1<<WDP0; //設定WDP[3:0]=1001，timeout時間為8秒  
  WDTCSR |= (1<<WDIE);  //設定WDT的執行模式為中斷模式
  Serial.println("Initialisation complete."); delay(100);
}

/***************************************************
 * loop
 ***************************************************/
void loop() {
  if(f_wdt == 1) {
    digitalWrite(LED_PIN,!digitalRead(LED_PIN));  //反轉LED現在的狀態    
    f_wdt = 0;
    enterSleep();  //進入睡眠模式
  } 
}
