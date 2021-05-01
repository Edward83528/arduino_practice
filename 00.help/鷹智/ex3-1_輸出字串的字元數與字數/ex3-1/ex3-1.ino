int A = 0 ;//char
int B = 1 ;//word 


void setup() {
 
Serial.begin(9600);
}

void loop() {  
  // 檢查是否有資料可供讀取
  if (Serial.available() > 0) {
    // 讀取進來的
    char c = Serial.read();
     Serial.print(c);
    
    if(c != '\n')    //沒有換行+1
      {
        A ++ ;
       }
    if(c == ' ') //每一個空格+1
      {
        B ++  ;
       }
    if(c == '\n' )
      {
       Serial.print("=> char=");
       Serial.print(A);
       Serial.print(" word=");
       Serial.println(B);
       A = 0 ;
       B = 0 ;
       }   
      
  }  


}
