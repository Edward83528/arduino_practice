#include <avr/wdt.h>
#define TIMEOUT WDTO_8S   //定義WDT的timeout時間
#define LED_PIN 13

/***************************************************
 * setup
 ***************************************************/
void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
  wdt_enable(TIMEOUT);  //啟用WDT，並設定timeout時間為8秒
  Serial.println("Start ...");
}

/***************************************************
 * loop
 ***************************************************/
void loop()
{
  char keyin;

  if(Serial.available()>0) {
     digitalWrite(LED_PIN,HIGH);
     keyin=Serial.read();
     if(keyin=='x') while(1);  //如果keyin=='x'，則進入無窮迴圈
     delay(100);
  }
  digitalWrite(LED_PIN,LOW);
  wdt_reset();  //清除WDT的計數值，避免系統重啟
}
