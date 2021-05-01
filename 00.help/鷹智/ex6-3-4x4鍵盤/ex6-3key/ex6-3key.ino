/**
** keypad
** 腾博科技有限公司
** 淘宝店网址 : http://shop68507353.taobao.com/
**/
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2,3,4,5}; // 按鍵模組，行1-4接腳對應到D2-D5。
byte colPins[COLS] = {6,7,8,9}; // 按鍵模組，列1-4接腳對應倒D6-D9。
// 初始化Keypad物件
// 語法：Keypad(makeKeymap(按鍵字元的二維陣列), 模組列接腳, 模組行接腳, 模組列數, 模組行數)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char key = keypad.getKey();// 透過Keypad物件的getKey()方法讀取按鍵的字元
  if (key != NO_KEY){  // 若有按鍵被按下…
    Serial.println(key);// 顯示按鍵的字元
  }
}
