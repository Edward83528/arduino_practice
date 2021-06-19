#include <wiring_private.h>


void setup() {

}

void loop() {
    pin3PWN(31, 95);
    delay(3000);
    pin3PWN(2000, 90);
    delay(3000);
}

int pin3PWN(int freq, int dc) {
    float TOP;
    int i, pre[6] = {
        8,
        32,
        64,
        128,
        256,
        1024
    };

    pinMode(3, OUTPUT);
    if (dc == 0) {
        digitalWrite(3, LOW);
        return 1;
    }
    if (dc == 100) {
        digitalWrite(3, HIGH);
        return 1;
    }
    // i 倍率
    for (i = 0; i < 6; i++) {
        TOP = 16000000 / pre[i] / freq / 2;
        if (TOP < 255 && TOP > 0) {
            OCR2A = TOP;
            break;
        }
    }

    switch (i) {
        case 0:
            sbi(TCCR2B, CS21);
            break;
        case 1:
            sbi(TCCR2B, CS21);
            sbi(TCCR2B, CS20);
        case 2:
            sbi(TCCR2B, CS22);
            break;
        case 3:
            sbi(TCCR2B, CS22);
            sbi(TCCR2B, CS20);
        case 4:
            sbi(TCCR2B, CS22);
            sbi(TCCR2B, CS21);
        case 5:
            sbi(TCCR2B, CS22);
            sbi(TCCR2B, CS21);
            sbi(TCCR2B, CS20);

    }

    sbi(TCCR2B, WGM22);
    sbi(TCCR2A, WGM20);

    OCR2B = OCR2A * dc / 100;
    sbi(TCCR2A, COM2B1);
    return 1;
}
