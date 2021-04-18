#include "seg7.h"
#define Button 10
const int potPin=A0;
int  num,flag=0;
int mask;

void setup() {
  pinMode(potPin,INPUT);
    Serial.begin(9600);
  seg7_x1_init(2);
  seg7_x1_display(0);
}

void loop() {
  int val;
  float volt;

  
  int i;
  for(int i=2;i<=7;i++){

  val=analogRead(potPin);
  volt=val*0.00488*400;
  Serial.print(volt,1);
  Serial.println('v');
    
    digitalWrite(i,HIGH);
    delay(volt);
    digitalWrite(i,LOW);
    }

}
