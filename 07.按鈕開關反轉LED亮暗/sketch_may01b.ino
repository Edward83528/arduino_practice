const int BUTTON_PIN = 7; // 按鍵的接腳
const int LED_PIN = 3; // LED燈的接腳

int buttonState = 0; // 按鈕的狀態
int buttonState_old = 0; // 上一次按鈕的狀態 比對上一個狀態的值(未按> buttonState==LOW && buttonState_old==HIGHT 按下> buttonState==HIGH && buttonState_old==LOW )

int state = 0; // LED 亮按狀態 0 暗,1 亮 

void setup() {
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT_PULLUP); // 設定按鈕的接腳為輸入，因為我們要讀取它的狀態
    pinMode(LED_PIN, OUTPUT); // 設定LED的PIN腳為輸出
}

void loop() {
    buttonState = digitalRead(BUTTON_PIN); //讀取按鍵的狀態
    //Serial.println(buttonState); // 不按:1 or 按:0
    if (buttonState == HIGH && buttonState_old == LOW) { // 如果按鍵按了
        state = 1 - state;
    }
    if ((buttonState == LOW && buttonState_old == HIGH)) {
        delay(10);
    }
    buttonState_old = buttonState;
    Serial.println(state); // 印出現在亮還不亮

    if (state == 1) {
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }

}