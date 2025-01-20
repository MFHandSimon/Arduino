const int dataPin = 18;
const int clockPin = 19;
const int latchPin = 23;
const int swA = 13;
const int swB = 16;
const byte NUM[] = { 0xFC, 0X60, 0XDA, 0XF2, 0X66, 0XB6, 0XBE, 0XE0, 0XFE, 0XF6, 0x2, 0x0 };
int scoreA = 0, scoreB = 0;
boolean recordFlag = false;
boolean displayFlag = true;
unsigned int preTime;

void setup() {
  pinMode(swA, INPUT);
  pinMode(swB, INPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, LOW);
  for (int i = 5; i >= 1; i--){
    specialDigitDispaly(2, i);
  delay(1000);}
}


void loop() {
  int valA = !digitalRead(swA);
  int valB = !digitalRead(swB);

  if (recordFlag == false) {
    if ((valA == 0) && (valB == 1)) {
      scoreA++;
      recordFlag = true;
    } else if ((valA == 1) && (valB == 0)) {
      scoreB++;
      recordFlag = true;
    }
  }
  if ((valA == 1) && (valB == 1))
    {recordFlag = false;delay(500);
    }
  if ((scoreA <= 1) && (scoreB <= 1))
    displayScore();
  else {
    while (true) {
      if ((millis() - preTime) > 200) {
        displayFlag = !displayFlag;
        preTime = millis();
      }
      if (displayFlag)
        displayScore();
      else
        displayEmpety();
    }
  }
}


void displayEmpety() {
  for (int i = 1; i <= 4; i++) {
    specialDigitDispaly(i, 11);
  }
}

void displayScore() {
  specialDigitDispaly(1, scoreA);
  specialDigitDispaly(2, 10);
  specialDigitDispaly(3, 10);
  specialDigitDispaly(4, scoreB);
}

void specialDigitDispaly(byte digit, byte num){ 
byte val = 0;
val = bitSet(val, digit - 1);
shiftOut(dataPin, clockPin, MSBFIRST, val);
shiftOut(dataPin, clockPin, LSBFIRST, ~NUM[num]); 
digitalWrite(latchPin, HIGH);
digitalWrite(latchPin, LOW);
}
