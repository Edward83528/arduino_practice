#include "seg7.h"

int num=0, flag=0;
void setup() {
 Serial.begin(9600); 
 pinMode (potPin,INPUT); 
 seg7_x1_init(2);
 seg7_x1_display(0);
}

void loop() {
  if(digitalRead(Button)==LOW)
  {num=++num%10; flag=1;}
  if(flag==1){
    seg7_x1_display(num);
    flag=0;
    }
}
