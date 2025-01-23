const int latchPin = 18, clockPin = 19, dataPin = 23, swPin = 2;
byte NUM[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6, 0x0};
int number = 0, num = 0;
bool flag = 0, _flag = 0;
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(swPin, INPUT);
  digitalWrite(latchPin, LOW);
  digitalWrite(clockPin, LOW);
  Display(10);
}

void loop() {
  int x = 0;
  if (digitalRead(swPin) && flag == 0) {
    while (digitalRead(swPin)) {
      delay(20);
    }
    number++;
  }
  if (number == 1 && flag == 0) {
    for (int i = 9; i >= 0; i--) {
      Display(i);
      delay(500);
    }
    flag = 1;
  }

  if (digitalRead(swPin) && flag == 1) {
    while (digitalRead(swPin)) {
      delay(20);
    }
    num++;
    if (num <= 5) {
      Display(num);
    }
    if (num == 6) {
      Display(4);
    }
    if (num == 7) {
      Display(3);
    }
    if (num == 8) {
      Display(2);
    }
    if (num == 9) {
      Display(1);
    }
    if (num == 10) {
      num = 2;
      Display(num);

    }
  }




}
void Display(byte num) {
  shiftOut(dataPin, clockPin, LSBFIRST, ~NUM[num]);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
}
