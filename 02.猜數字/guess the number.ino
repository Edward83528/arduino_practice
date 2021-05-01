String str; // 存取使用者輸入
String answer = "456"; // 正確答案

void setup() {

    Serial.begin(9600); // 設定鮑率

    Serial.setTimeout(10); // 設定為每10毫秒結束一次讀取

}

void loop() {

    // 有輸入狀況
    if (Serial.available()) {

        str = Serial.readString(); // 讀取輸入字串
        int maxLength = str.length() - 1;
        if (maxLength == 3) {
            int answerA = 0; // 存取A
            int answerB = 0; // 存取B
            // 跑字串長度
            for (int i = 0; i < str.length(); i++) {
                char answercharAt = answer.charAt(i);
                char strcharAt = str.charAt(i);
                if (answercharAt == strcharAt) {
                    answerA++;
                } else {
                    if (answer.indexOf(strcharAt) != -1) {
                        answerB++;
                    }
                }

            }

            if (answerA == 3 && answerB == 0) {
                Serial.print("=================Good Job. You got it.");
                Serial.print("\n");
            } else {
                Serial.print("You guess:" + str + "=> Ans=" + String(answerA) + "A" + String(answerB) + "B");
                Serial.print("\n");
            }

        } else {
            Serial.print("應該輸入3位數字");
            Serial.print("\n");
        }

    }

}
