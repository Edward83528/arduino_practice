#define Ball 3  //指定滾珠開關的接腳為D3
#define Led 13  //指定LED的接腳為D13
int flag ;
int step_num =0 ;
void setup() {
  Serial.begin(9600);
  pinMode(Ball,INPUT_PULLUP); //設定滾珠開關接腳，並啟用內建的上拉電阻
  pinMode(Led,OUTPUT);       //設定LED接腳為輸出模式
  EIMSK |= _BV(INT1);      //enable INT0。EIMSK 1= 00000001，OR強迫變為1
  EICRA &= ~_BV(ISC00);    //觸發模式設為CHANGE(ISC01=0,ISC00=1)。00000001->11111110  AND 反向變為0
  EICRA |= _BV(ISC01);
    
}

void loop() {
if(flag==1){
  {
    flag =0 ;
    Serial.print("計數:");
    Serial.println(step_num);      
    
      }

 }

}

void my_ISR(){

flag=1 ;
if(digitalRead(Ball)==LOW)   //讀取滾珠開關接腳的電位是否為LOW
    digitalWrite(Led,HIGH); 
step_num ++;

 
 
//INT0固定呼叫的中段處理函式

}
ISR(INT1_vect)
{
  my_ISR();
  delay(5000);
  }
