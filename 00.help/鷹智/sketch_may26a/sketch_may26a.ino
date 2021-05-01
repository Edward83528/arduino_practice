const byte colPins[4] = {4,5,6,7};
const byte rowPins[4] = {8,9,10,11};
const char keymap[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte i,j;
byte scanVal;
int flag ;
char scan;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  PCICR |= 0b00000001;
  PCMSK0 |= 0b00001111;
    for (i = 0; i <= 3; i++) {
    pinMode(rowPins[i], INPUT);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
    digitalWrite(rowPins[i], HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(flag==1){
    Serial.println(scan);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    flag=0;
  }
}

void my_ISR(){
  flag=1; 
  for (i = 0; i <= 3; i++) {
    for (j = 0; j <= 3; j++) {
      digitalWrite(colPins[j], LOW);
      scanVal = digitalRead(rowPins[i]);
 
      if (scanVal == LOW) {    // 如果輸入值是「低電位」…
        scan=keymap[i][j];  // 輸出按鍵代表的字元
        delay(200);  // 掃描按鍵的間隔時間
        digitalWrite(colPins[j], HIGH);
        break;       // 跳出迴圈
      }
      digitalWrite(colPins[j], HIGH);
    }
  }
}

ISR(PCINT0_vect){
  my_ISR();
}
