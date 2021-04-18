const byte colPins[4] = {4,5,6,7};     // 設定「行」腳位
const byte rowPins[4] = {8,9,10,11}; // 設定「列」腳位
const char keymap[4][4] = {                   // 設定按鍵的「行、列」代表值
                          {'1','2','3','A'}, 
                          {'4','5','6','B'}, 
                          {'7','8','9','C'},
                          {'*','0','#','D'}
                          };


byte i, j;// 暫存迴圈的索引數字
byte scanVal;   // 暫存掃描到的按鍵值
volatile byte row = 0;
volatile byte col = 0;
volatile int flag = 0;

void setup(){
  Serial.begin(9600);
  row=0 ;  col=0 ; flag=0;
  PCICR |= 0b00000001;    // Enables PCINT0
  PCMSK0 |= 0b00001111; // PCINT0choose D8, D9, D10, D11 to be active
  
    
  for (i = 0; i <= 3; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
    pinMode(rowPins[i], INPUT_PULLUP);
  }
}
 
void loop() {
   if(flag==1) {  //鍵盤中斷時flag=1
      Serial.println(keymap[row][col]);
      delay(400);
       flag=0;  
   }
}
ISR(PCINT0_vect)
{
   my_ISR();
 }
   
void my_ISR(){
 for(i=0; i<=3; i++)digitalWrite(colPins[i], HIGH); //設定colpin to HIGH

 for (i=0; i<=3; i++) { //col
    digitalWrite(colPins[i], LOW);

    for (j=0; j<=3; j++) { //row

      scanVal = digitalRead(rowPins[j]);
      if (scanVal == 0) {    // 如果輸入值是「低電位」…
         col = i; row = j;
         flag = 1;
      }
    }

    digitalWrite(colPins[i], HIGH);
  }
  
  for(i=0; i<=3; i++)digitalWrite(colPins[i], LOW); //設定colpin to LOW 重新獲得中斷能力
}
