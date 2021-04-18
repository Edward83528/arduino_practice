#include "seg7.h"
const int potPin=A0;
int val ;
float x;
int num ;
void setup() {
  seg7_x1_init(2);
  seg7_x1_display(0);
  pinMode(potPin,INPUT);
  Serial.begin(9600);

}

void loop() {
  
  val=analogRead(potPin); //讀取可變電阻的值(0-1023)
  x=map(val,0,1023,100,2000); //可變電阻數值0-1023按比例縮放為100-2000
  
  
  Serial.print(x);
  Serial.println("ms");
  delay(x);
  num=++num%6;//修改seg7.h
  seg7_x1_display(num);
  

}
