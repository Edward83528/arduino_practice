const int LedPin = 9;
const int PotPin = A0;

int brightness = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode( LedPin , OUTPUT );
  pinMode( PotPin , INPUT );
 }

void loop() {
  // put your main code here, to run repeatedly:
  int val;
  float mLight;
  val = analogRead(PotPin);
  mLight = map(val,0,1023,0,255);
  analogWrite( LedPin , mLight );
  Serial.println(mLight);


}
