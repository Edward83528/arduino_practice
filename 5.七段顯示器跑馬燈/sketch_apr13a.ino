#include "seg7.h"
#define Button 10
int  num,flag=0;
int mask;

void setup() {
  //pinMode(Button.INPUT_PULLUP);
  seg7_x1_init(2);
  seg7_x1_display(0);
}

void loop() {
  int i;
  for(int i=2;i<=7;i++){
    digitalWrite(i,HIGH);
    delay(1000);
    digitalWrite(i,LOW);
    }

}
