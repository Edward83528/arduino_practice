#include <Keypad.h>
#include "seg7.h"

#define KEY_ROWS 4 // 按鍵模組的列數
#define KEY_COLS 4 // 按鍵模組的行數
//#define ButtonI2 2
//#define ButtonI3 3 

int num;

char keymap[KEY_ROWS][KEY_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte colPins[KEY_COLS] = {9, 8, 7, 6};     // 按鍵模組，行1~4接腳。
byte rowPins[KEY_ROWS] = {13, 12, 11, 10}; // 按鍵模組，列1~4接腳。 

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //pinMode(ButtonI2,INPUT_PULLUP);
  //pinMode(ButtonI3,INPUT_PULLUP);

  //attachInterrupt(digitalPinToInterrupt(ButtonI2),my_ISR_B2,FALLING);
  //attachInterrupt(digitalPinToInterrupt(ButtonI3),my_ISR_B3,FALLING);

  //seg7_x4_init(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = myKeypad.getKey();
  
  if (key){  // 若有按鍵被按下…
    Serial.println(key);  // 顯示按鍵的字元
  }
  /*
  int dig0,dig1,dig2,dig3;

  if(Serial.available())
  { 
    num=random(0,10000); 
    Serial.println(num); 
    Serial.read();
  }
  dig3=num/1000;
  seg7_x4_display(3,dig3);
  delay(5);
  dig2=(num/100)%10;
  seg7_x4_display(2,dig2);
  delay(5);
  dig1=(num/10)%10;
  seg7_x4_display(1,dig1);
  delay(5);
  dig0=num%10;
  seg7_x4_display(0,dig0);
  delay(5);*/
  
}

void my_ISR_B2() {
  Serial.println("Push B2"); 
}

void my_ISR_B3() {
  Serial.println("Push B3"); 
}
