const byte colPins[4] = {
    9,
    8,
    7,
    6
};
const byte rowPins[4] = {
    13,
    12,
    11,
    10
};
const char keymap[4][4] = {
    {
        '1',
        '2',
        '3',
        'A'
    },
    {
        '4',
        '5',
        '6',
        'B'
    },
    {
        '7',
        '8',
        '9',
        'C'
    },
    {
        '*',
        '0',
        '#',
        'D'
    }
};
byte i, j;
byte scanVal;

void setup() {

    // 設定Rate
    Serial.begin(9600);

    for (i = 0; i <= 3; i++) {
        pinMode(rowPins[i], INPUT);
        pinMode(colPins[i], OUTPUT);
        digitalWrite(colPins[i], HIGH);
        digitalWrite(rowPins[i], HIGH);
    }
}
void loop() {
    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 3; j++) {
          
            digitalWrite(colPins[j], LOW);
            scanVal = digitalRead(rowPins[i]);
            if (scanVal == LOW) {
                Serial.println(keymap[i][j]);
                delay(200);
                digitalWrite(colPins[j], HIGH);
                break;
            }
            digitalWrite(colPins[j], HIGH);
            
        }
    }
}
