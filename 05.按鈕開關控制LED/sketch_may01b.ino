const int BUTTON_PIN = 7;  // 按鍵的接腳
const int LED_PIN =  3;   // LED燈的接腳

int buttonState = 0;   // 按鈕的狀態

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // 設定按鈕的接腳為輸入，因為我們要讀取它的狀態
  pinMode(LED_PIN, OUTPUT);   // 設定LED的PIN腳為輸出
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);  // 讀取按鍵的狀態
  Serial.println(buttonState); // 未按:1 or 按:0
  if(buttonState == LOW){          // 如果按鍵按了
    digitalWrite(LED_PIN, HIGH);   // LED就亮了 
  }else{                           // 如果按鍵是未按下
    digitalWrite(LED_PIN, LOW);    // LED就不亮
  }
}
