#include "seg7.h"


int num;
void setup() {
  
  seg7_x4_init(2);
  
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  num=random(0,10000);
  
}

void loop() 
{

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
  delay(5);

}
