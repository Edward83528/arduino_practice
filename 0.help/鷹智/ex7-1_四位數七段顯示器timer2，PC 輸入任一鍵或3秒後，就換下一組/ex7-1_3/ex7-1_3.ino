#include "ex7-1.h"
int num;
int count =0;
int countb =0;
int flag =0;

void timer2(){
  //TCCR2A = TCCR2A & B11111100; //set TCCR2A中的WGM21和WGM20的值為0
  //TCCR2B = TCCR2B & B11110000; //set TCCR2A中的CS22、CS21和CS20的值為0
  //TCNT2 = 0;  //initialize counter to 0。儲存定時器的數值

  TCCR2A = 0; //set entire TCCR2A reg to 0
  TCCR2B = 0; //same for TCCR2B
  TCNT2 = 0;  //initialize counter to 0
  TCCR2A = TCCR2A | (1<<WGM02); // turn on CTC mode (21)
   
  //TCCR2A =(1<<WGM21); // turn on CTC mode 
    
 //TCCR2B = (1<<CS12);   //(22)CS12=2定義在time.h，設定定時器的時脈來源及預先儲頻prescaler的倍數有1/8、1/64、1/256、1/1024四種有效除頻倍數
  TCCR2B = TCCR2B | (1<<CS12);   //(22)
  //觸發中斷的目標值，當TCNTx的計數值等於OCR2A的內容值就會觸發中斷
  //TOP= T*16M/256(來自prescaler電路除頻倍數) =62500MHz=62.5KHz，定時器的時脈來源及其除頻倍數timer2 256倍)，16MHz(1秒有16x10^6個脈波)
  OCR2A = 62.5;
  TIMSK2 = TIMSK2 | (1<<OCIE2A); // enable timer compare interrupt，OCIE12A=2定義在time.h中，用來啟用或停用定時器的中斷，輸出比較A中斷、輸出比較B中斷、以及溢位中斷3種中斷
}

void setup() {
  Serial.begin(9600);
  seg7_x4_init(2);
  randomSeed(analogRead(A0));//類比輸入讀取0-1023
  //num=random(0,10000);
  timer2();
}

void loop() {
  if(Serial.available()) { 
    num=random(0,10000); //0-9999
    Serial.println(num); 
    Serial.read(); 
    count=0;
    flag=1;
    } 
    //Seg7x4_show();
 }

ISR(TIMER2_COMPA_vect)
{
   // every interrupt counts will +1，
  // 計算count當加到 counts=3000(each interrupt cost 0.001sec，3000=3sec) print random number，在歸零
  count++;
  countb++;
  if(count == 3000){ //每3秒就執行一次，一毫秒累積3000次之後就等同3000毫秒的效果
    num = random(0,10000);
    Serial.println(num);
    Serial.read();
    count=0;
    //Seg7x4_show();
  }
  if(countb == 10 or flag == 1){
   
    countb = 0;
    flag = 0;
    Seg7x4_show();
  }
 }
void Seg7x4_show(){
int dig0,dig1,dig2,dig3,D1;
D1=3;
dig3 = num/1000;
seg7_x4_display(3, dig3);
delay(D1);
dig2=(num/100)%10;
seg7_x4_display(2,dig2);
delay(D1);
dig1=(num/10)%10;
seg7_x4_display(1,dig1);
delay(D1);
dig0=num%10;
seg7_x4_display(0,dig0);
delay(D1);
  }
