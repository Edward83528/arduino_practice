#include "seg7.h"
#define Button 10
const int potPin=A0;
int  num,flag=0;
int mask;

void setup() {
  pinMode(potPin,INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  seg7_x1_init(2);
  seg7_x1_display(0);
}

void loop() {
  int val;
  float volt;

  //Serial.println(j);
  
  int i;
  int j;
  for(int i=0;i<10;i++){
  j=random(0,10);
  val=analogRead(potPin);
  volt=val*2.737+200;

  Serial.println(volt,1);
    seg7_x1_display(j);
    delay(volt);
    
    }

}
