#include "seg7.h"
#define Button 10

int num = 0 ,flag=0;



const int potPin=A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Button,INPUT_PULLUP);
  seg7_x1_init(2);
  seg7_x1_display(0);
  pinMode(potPin,INPUT);
  Serial.begin(9600);
  
  
  
}

void loop() {
  
  int val;
  float myDeay;
  
  val = analogRead(potPin);

  myDeay = map(val,0,1023,100,2000);
  

  Serial.print(myDeay);
  Serial.println("MS");
  delay(myDeay);
  num=++num%6;
  seg7_x1_display(num);
  
  /*
  // put your main code here, to run repeatedly:
  if(digitalRead(Button)==LOW)
  {
    num=++num%6;
    flag = 1; 
    delay(100);
  }
 
  if(flag==1)
  {
    seg7_x1_display(num);
    flag=0;  
    Serial.println(num);
  }*/
}
