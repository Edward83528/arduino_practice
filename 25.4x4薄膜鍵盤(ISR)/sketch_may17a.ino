const byte colPins[4] = {4,5,6,7};     // 設定「行」腳位
const byte rowPins[4] = {8,9,10,11}; // 設定「列」腳位
const char keymap[4][4] = {                   // 設定按鍵的「行、列」代表值
                          {'1','2','3','A'}, 
                          {'4','5','6','B'}, 
                          {'7','8','9','C'},
                          {'*','0','#','D'}
                          };
int flag ;
char key ;
byte i, j; // 暫存迴圈的索引數字
byte scanVal; // 暫存掃描到的按鍵值

void setup() {
    Serial.begin(9600);
    PCICR |= 0b00000001; // Enables PCINT0
    PCMSK0 |= 0b00001111; // PCINT0 choose D8, D9, D10, D11 to be active

    for (i = 0; i <= 3; i++) {
        pinMode(colPins[i], OUTPUT);
        digitalWrite(colPins[i], LOW);
        pinMode(rowPins[i], INPUT_PULLUP);
        digitalWrite(rowPins[i], HIGH);
    }
}

void loop() {
    if (flag == 1) { //鍵盤中斷時flag=1
        Serial.println(key); // 印出鍵盤字符
        // 重置
        for (i = 0; i <= 3; i++) {
            digitalWrite(colPins[i], LOW);
            digitalWrite(rowPins[i], HIGH);
        }
        flag = 0;

    }
}

void my_ISR() {
    flag = 1; // 中斷flag設1
    for (i = 0; i <= 3; i++) { //row
        for (j = 0; j <= 3; j++) { //col
            digitalWrite(colPins[j], LOW);
            scanVal = digitalRead(rowPins[i]);

            if (scanVal == LOW) { // 如果輸入值是「低電位」…
                key = keymap[i][j]; // 輸出按鍵代表的字元
                delay(200); // 掃描按鍵的間隔時間
                digitalWrite(colPins[j], HIGH);
                break; // 跳出迴圈
            }
            digitalWrite(colPins[j], HIGH);
        }
    }
}

// 我是用D8, D9, D10, D11 所以 PCINT0(PCINT0_vect)為固定呼叫的中斷處理函式
ISR(PCINT0_vect) {
    my_ISR();
}

 
 
