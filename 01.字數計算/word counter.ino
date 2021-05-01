String str; // 存取使用者輸入
int strLength; // 存取字串長度


void setup() {

    Serial.begin(9600); // 設定鮑率

    Serial.setTimeout(10); // 設定為每10毫秒結束一次讀取

}

void loop() {

    // 有輸入狀況
    if (Serial.available()) {

        str = Serial.readString(); // 讀取輸入字串
        strLength = str.length() - 1; // 算出字串長度,但要減掉空終止字串
        int words = 0; // 存取單字數

        // 跑字串長度,遇到空白累加(算空白個數)
        for (int i = 0; i < strLength; i++) {
            if (str[i] == ' ') {
                words++;
            }
        }
        Serial.print(str + "=> char=" + String(strLength) + " word=" + String((words + 1))); // 單字數=空白數+1
        Serial.print("\n");

    }

}
