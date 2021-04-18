#include "ex7-1.h"
int num;
unsigned int count =0; //unsigned 則全部都是正數 0-~65535
unsigned int value =0;

/***************************************************
 * 設定定時器
 ***************************************************/
void SetupTimer(void)
{
 //---step1:初始暫存器
  TCCR2B = 0;// 歸0，時脈來源與除頻prescaler的倍數，1/8、1/64、1/256
  TCNT2  = 130;//storage counter value 130 out of 255
  TIFR2  = 0x00; //Timer2 INT Flag Reg :Clear Timer Overflow Flag(發生中斷時旗標欄位預設1，執行中斷後硬體欄位清除為0)
 //---step2:設定CTC模式
  TIMSK2 = 0x01;  // enable timer compare interrupt(啟用或停用暫存器的中斷)
 //---step3:設定預先除頻倍數prescaler與正確的TOP上限值
  TCCR2A = 0x00; //Timer2 Control Reg A: Wave Gen Mode normal
  TCCR2B = 0x05; //Timer2 Control Reg B: Timer Prescaler set to 128
  //OCR2A = 249; = (16*10^6) / (8000*8) - 1 (must be <256)，set compare match register for 8khz increments
}
void setup() {
  Serial.begin(9600);
  seg7_x4_init(2);
  randomSeed(analogRead(A0));//類比輸入讀取0-1023
  num=random(0,10000);
  SetupTimer(); 
  
 }

void loop() {
  //int dig0,dig1,dig2,dig3;

  if(Serial.available()) {
    num=random(0,10000); Serial.read();//0-9999
    } 
  if (value ==1){
    num=random(0,10000); 
    value = 0 ;
    }
  seg7X4Show();
  //dig3=num/1000;
  //seg7_x4_display(3,dig3);
  //delay(2);
  //dig2=(num/100)%10;
  //seg7_x4_display(2,dig2);
  //delay(2);
  //dig1=(num/10)%10;
  //seg7_x4_display(1,dig1);
  //delay(2);
  //dig0=num%10;
  //seg7_x4_display(0,dig0);
  //delay(2);
}

ISR(TIMER2_OVF_vect)
{
   count ++; // Increments the interrupt counter
   if(count >3000 ){
    value = 1;
    count =0;   //Rest the interrupt counter
        }
    TCNT2 = 130; //Rest timer to 130 out of 255
    TIFR2  = 0x00; //Timer2 INT Flag Reg :Clear Timer Overflow Flag  
    };
void seg7X4Show()
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
