#include "seg7.h"
#define Button 10
int  num,flag=0;

void setup() {
  //pinMode(Button.INPUT_PULLUP);
  seg7_x1_init(2);
  seg7_x1_display(0);
}

void loop() {
  int i;
  for(int i=0;i<10;i++){
    
    seg7_x1_display(i);
    delay(1000);
   
    }

}
