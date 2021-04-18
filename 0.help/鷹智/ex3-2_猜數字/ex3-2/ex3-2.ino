
String Answer="124"; //內定數值124
String Guess;
int T = 0 ; //答對
int F = 0 ; //答錯

void setup() {
 
Serial.begin(9600);
}

void loop() {  
  // 檢查是否有資料可供讀取
  if (Serial.available() > 0) {
    // 讀取進來的
      Guess = Serial.readString();
    Serial.print("You guess: ");
    Serial.print(Guess);
     
    
      //判斷幾A幾B

            for (int i=0; i<3; i++)
            {
                for (int j=0; j<3; j++)
                {
                    if((Answer[i] == Guess[j])&&(i == j))
                    {
                        T++; //值和位置相同=A
                    }                      
                    else if((Answer[i] == Guess[j])&&(i != j))
                    {
                        F++; //值相同位置不同=B
                    }
                }
            }
            //輸出

            if (T == 3)
            {
                 Serial.print("Ans=>");
                 Serial.print(T);
                 Serial.print("A");
                 Serial.print(F);
                 Serial.println("B");
                 Serial.print("=================Good Job. You got it."); 
                                   
            }
            
             else
            {
                Serial.print("Ans=>");
                Serial.print(T);
                Serial.print("A");
                Serial.print(F);
                Serial.println("B");
                
                           
            }

         T = 0 ;
        F = 0 ;

        }

        
    

    }

      
