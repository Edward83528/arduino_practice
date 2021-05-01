/*** seg7.h ***/
const byte seg7_digit[10]={ B10000000,  //數字0
							B01000000,  //數字1
							B00100000,  //數字2
							B00010000,  //數字3
							B00001000,  //數字4
							B00000100,  //數字5
							B10111110,  //數字6
							B11100100,  //數字7
							B11111110,  //數字8
							B11110110}; //數字9
int seg7_x1_FirstPin;  //一位數七段顯示器的第一隻接腳
int seg7_x4_FirstPin;  //四位數七段顯示器的第一隻接腳

//*** 初始化一位數七段顯示器8隻連續的接腳
void seg7_x1_init(int pin) {
  seg7_x1_FirstPin=pin;  //設定一位數七段顯示器的第一隻接腳
  for(int i=0; i<8; i++) pinMode(seg7_x1_FirstPin+i, OUTPUT);
}

//*** 一位數七段顯示器顯示數字
void seg7_x1_display(int num) {
byte mask;

  for(int i=0; i<8; i++)  {
    mask=B10000000>>i;  //將1右移到正確的位置
    if(seg7_digit[num] & mask) digitalWrite(seg7_x1_FirstPin+i, HIGH);
    else digitalWrite(seg7_x1_FirstPin+i, LOW);
  }
}

//*** 初始化四位數七段顯示器12隻連續的接腳
void seg7_x4_init(int pin) {
  seg7_x4_FirstPin=pin;  //設定四位數七段顯示器的第一隻接腳
  for(int i=0; i<12; i++) pinMode(seg7_x4_FirstPin+i, OUTPUT);
}

//*** 四位數七段顯示器顯示數字
void seg7_x4_display(int digit, int num) {
byte mask;

  //先關掉四顆七段顯示器
  for(int i=8; i<12; i++) digitalWrite(seg7_x4_FirstPin+i, LOW);
  //再致能指定的七段顯示器
  switch(digit) {
    case 0: digitalWrite(seg7_x4_FirstPin+8, HIGH); break;
    case 1: digitalWrite(seg7_x4_FirstPin+9, HIGH); break;
	case 2: digitalWrite(seg7_x4_FirstPin+10, HIGH); break;
	case 3: digitalWrite(seg7_x4_FirstPin+11, HIGH); break;
  }
  //顯示數字
  for(int i=0; i<8; i++)  {
    mask=B10000000>>i;
    if(seg7_digit[num] & mask) digitalWrite(seg7_x4_FirstPin+i, HIGH);
    else digitalWrite(seg7_x4_FirstPin+i, LOW);
  }
}
