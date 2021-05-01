#include <Wire.h>
void setup() {
  Serial.begin(9600);
  Serial.println("12C Slave Scanning....");
  Wire.begin();                             //將本裝置初始成master
  for(byte addr=8; addr<120; addr++){       //將位址8開始掃描到位址119
                                            
    Wire.beginTransmission(addr);           //開始傳送資料到指定的Slave位址
    if(Wire.endTransmission()==0){          //假如有回傳ACK就顯示其位址
      Serial.print("Find slave at:0X");
      Serial.println(addr, HEX);
      
      }
    
    }
  Serial.println("END....");
}

void loop() {
  // put your main code here, to run repeatedly:

}
