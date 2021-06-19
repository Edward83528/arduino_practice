/*** 無源蜂鳴器範例 ***/ #include "music.h"  //載入音樂定義檔

#define Button 2 //指定按鈕開關的接腳為D2
#define Buzzer 3 //指定蜂鳴器的接腳為D3
int num = -1, flag = 0;
int speed[3] = {
    S140,
    S80,
    S60
}; //三首歌的速度
//定義音高,XX表結束
int pitch[3][30] = {
    {
        G4,
        E4,
        E4,
        0,
        F4,
        D4,
        D4,
        0,
        C4,
        D4,
        E4,
        F4,
        G4,
        G4,
        G4,
        0,
        XX
    }, //小蜜蜂
    {
        C4,
        C4,
        D4,
        E4,
        E4,
        D4,
        C4,
        D4,
        E4,
        C4,
        0,
        E4,
        E4,
        F4,
        G4,
        G4,
        F4,
        E4,
        F4,
        G4,
        E4,
        0,
        XX
    }, //蝴蝶
    {
        C4,
        C4,
        D4,
        F4,
        G4,
        F4,
        G4,
        A4,
        0,
        C5,
        A4,
        A4,
        G4,
        F4,
        G4,
        0,
        0,
        XX
    }
}; //望春風
//定義節拍
float tempo[3][30] = {
    {
        T4,
        T4,
        T4,
        T4,
        T4,
        T4,
        T4,
        T4,
        T4,
        T4,
        T4,
        T4,
        T4,
        T4,
        T4,
        T4
    }, //小蜜蜂
    {
        T4,
        T8,
        T8,
        T4,
        T4,
        T8,
        T8,
        T8,
        T8,
        T4,
        T4,
        T4,
        T8,
        T8,
        T4,
        T4,
        T8,
        T8,
        T8,
        T8,
        T4,
        T4
    }, //蝴蝶
    {
        T4d,
        T8,
        T4,
        T4,
        T4,
        T8,
        T8,
        T4,
        T4,
        T4d,
        T8,
        T8,
        T8,
        T4,
        T2,
        T4,
        T4
    }
}; //望春風

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
        play(num);
        flag = 0;
    }
}

void play(int num) {
    int i, T1time, duration;
    T1time = 4 * 60000 / speed[num]; //計算全音符T1的時間(ms)
    for (i = 0;; i++) {
        if (pitch[num][i] == 9999) return; //判斷結尾       
        duration = T1time * tempo[num][i]; //計算節拍時間(ms)
        tone(Buzzer, pitch[num][i], duration / 2); //演奏一半
        delay(duration / 2); //停頓一半，才不會所有的音都連在一起
    }
}
