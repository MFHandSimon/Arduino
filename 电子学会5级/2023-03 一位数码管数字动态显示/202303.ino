#include <String.h>
const byte NUM[] {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6, 0x0};
const byte digitDisplay[] {0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};
const int latchPin = 18;
const int clockPin = 19;
const int dataPin = 23;
const int touchPin = T0;
const int threshold = 35;
bool touchDetected = false;
bool touch = false;
int touchVal;
String dispData;
char c;
String s;
int receData;
void setup() {
  Serial.begin(115200);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(latchPin, LOW);
  digitalWrite(clockPin, LOW);
  specialDigitDisplay(10);
}

void loop() {
  if (!touch) {
    touchSw();
  }
  int dispData = 0b11111111;
  if (Serial.available()) {
    receData = Serial.parseInt();
    Serial.println(receData);
    for (int i = 7; i >= 0; i--) {
      bitWrite(dispData, i, bitRead(~NUM[receData], i));
      shiftOut(dataPin, clockPin, LSBFIRST, dispData);
      digitalWrite(latchPin, HIGH);
      digitalWrite(latchPin, LOW);
      delay(500);
    }
  }
}

void specialDigitDisplay(byte num) {
  shiftOut(dataPin, clockPin, LSBFIRST, ~NUM[num]);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
}


void dao_ji_shi() {
  for (int i = 9; i >= 0; i--) {
    specialDigitDisplay(i);
    delay(500);
  }
}

void touchDoing() {
  touchDetected = true;
}

void touchSw() {
  touchVal = touchRead(touchPin);
  touchAttachInterrupt(touchPin, touchDoing, threshold);
  //  Serial.println("Value:" + String(touchVal));
  if (touchDetected) {
    //    Serial.println("触摸传感器已触发");
    dao_ji_shi();
    touchDetected = false;
    touch = true;
  }
  delay(200);
}
