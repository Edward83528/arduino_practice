/*** 有源蜂鳴器範例 ***/
#define Button 2 //指定按鈕開關的接腳為D2
#define Buzzer 3 //指定蜂鳴器的接腳為D3
int num = -1, flag = 0;

void setup() {
    pinMode(Button, INPUT_PULLUP); //設定Button接腳，並啟用內建的上拉電阻
    pinMode(Buzzer, OUTPUT); //設定蜂鳴器接腳為輸出模式
}

void loop() {
    if (digitalRead(Button) == LOW) //讀取Button接腳的電位是否為LOW
    {
        num = ++num % 3;
        flag = 1;
    } //若是，就代表按下開關，num+1後取3的餘數
    if (flag == 1) {
        switch (num) {
            case 0:
                play0();
                break;
            case 1:
                play1();
                break;
            case 2:
                play2();
        }
        flag = 0;
    }
}

void play0() {
    for (int i = 0; i < 10; i++) {
        digitalWrite(Buzzer, HIGH);
        delay(50);
        digitalWrite(Buzzer, LOW);
        delay(200);
    }
}

void play1() {
    for (int i = 0; i < 5; i++) {
        digitalWrite(Buzzer, HIGH);
        delay(600);
        digitalWrite(Buzzer, LOW);
        delay(100);
    }
}

void play2() {
    for (int i = 0; i < 5; i++) {
        digitalWrite(Buzzer, HIGH);
        delay(300);
        digitalWrite(Buzzer, LOW);
        delay(50);
        digitalWrite(Buzzer, HIGH);
        delay(50);
        digitalWrite(Buzzer, LOW);
        delay(50);
        digitalWrite(Buzzer, HIGH);
        delay(50);
        digitalWrite(Buzzer, LOW);
        delay(50);
    }
}
