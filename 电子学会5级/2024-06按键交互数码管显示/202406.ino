const int latchPin = 18, clockPin = 19, dataPin = 23, swPin = 2;
byte NUM[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
int oldtime = 0, display_number = 0, sw = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(swPin, INPUT);
  digitalWrite(latchPin, LOW);
  digitalWrite(clockPin, LOW);

}

void loop() {
  if (digitalRead(swPin)) {
    while (digitalRead(swPin)) {
      delay(20);
      display_number = -1;
    }
    sw++;
  }
  if (sw == 0) {
    display_four(0, 6, 3, 0);
  }
  if (millis() - oldtime >= 500) {
    oldtime = millis();
    display_number++;
    if (display_number > 9) {
      display_number = 0;
    }
  }
  if (sw == 1) {
    for (int i = 0; i <= 9; i++) {
      specialDigitDisplay(1, display_number);
    }
  }
  if (sw == 2) {
    for (int i = 0; i <= 9; i++) {
      specialDigitDisplay(2,  display_number);
    }
  } if (sw == 3) {
    for (int i = 0; i <= 9; i++) {
      specialDigitDisplay(3,  display_number);
    }
  } if (sw == 4) {
    for (int i = 0; i <= 9; i++) {
      specialDigitDisplay(4,  display_number);
    }
  }
  if (sw == 5) {
    sw = 1;
  }
}

void specialDigitDisplay(byte digit, byte num) {
  byte val = 0;
  val = bitSet(val, digit - 1);
  shiftOut(dataPin, clockPin, MSBFIRST, val);
  shiftOut(dataPin, clockPin, LSBFIRST, ~NUM[num]);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
}

void display_four(int a, int b, int c, int d) {
  specialDigitDisplay(1, a);
  specialDigitDisplay(2, b);
  specialDigitDisplay(3, c);
  specialDigitDisplay(4, d);
}
