// 控制 LED on pin 13亮滅, 每秒閃爍 2 次: 亮 0.25 秒滅 0.25 秒 ...
// LED on pin 8 每秒閃爍 1 次: 亮 0.5 秒滅 0.5 秒 ...
#define bbs(x)  (1<<x)
const int intA = 2500;   // 2500 * 0.1 ms = 250ms
const int intB = 5000;   // 5000 * 0.1 ms = 500ms = 0.5秒
// Prescaler 用 64
volatile int ggyy = 1;  // 使用這當 Flag 給  ISR 使用 !
int ledPin =13;
int led8 = 8;  // pin 8
/// For Prescaler == 64
///  1 秒 / (16 000 000 / 64) = 1/250000 =  0.000004 sec / per cycle
/// 0.1 sec / 0.000004 sec -1 = 25000 -1 = 24999
/// 0.0001 sec / 0.000004 sec -1 = 25 -1 = 24
const uint8_t myTOP = 24;  // 0.0001 sec when Prescaler == 64
///// Interrupt Service Routine for TIMER1 CTC on OCR1A as TOP
/// 注意以下名稱是有意義的, 不可亂改 !
ISR(TIMER2_COMPA_vect)
{
   static unsigned int aaa = 0;
   static unsigned int bbb = 0;
   ++aaa; bbb++;
   if(aaa == intA){
      aaa=0; myJobOne( );
   }
   if(bbb == intB){
      bbb=0; myJobTwo( );
   }
}
void setup( ) {
  pinMode(ledPin, OUTPUT);
  pinMode(led8, OUTPUT); digitalWrite(led8, 1); // 故意
  digitalWrite(ledPin, LOW); // turn Off the LED
  setMyTimer2( );
}
void loop() {
  //... 做其他事
  // if( ggyy == 1) ...
}
void myJobOne( ) {
  digitalWrite(ledPin, ggyy);  // ggyy 是 0 或 1
  ggyy = 1 - ggyy; //  給下次進入 用
}
void myJobTwo( ) {
  digitalWrite(led8, ! digitalRead(led8));  // Toggle led8
}
////////
void setMyTimer2( ){
  cli();  // 禁止中斷
  TCCR2A = bbs(WGM21);  // CTC mode 2; Clear Timer on Compare, see p.158-162
  TCCR2B = bbs(CS22);  // Prescaler == 64; see p.162 in datasheet 
  ///// 注意 WGM22 在 TCCR2B, 但 WGM21 與 WGM20 在 TCCR2A; 
  ///// mode 由 WGM22, WGM21, WGM20 決定 (see datasheet p.158-162)
  OCR2A = myTOP;  // TOP count for CTC, 與 prescaler 有關
  TCNT2=0;  // counter 歸零 
  TIMSK2 |= bbs(OCIE2A);  // enable CTC for TIMER2_COMPA_vect
  sei();  // 允許中斷
}
