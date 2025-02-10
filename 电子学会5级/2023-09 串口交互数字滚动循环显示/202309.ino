const int l = 18, c = 19, d = 23;
const byte num[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
byte arrayNum[4] {0, 2, 1, 1};
String receData = "";
unsigned int preTime;
boolean flag = true;
int dispData, interval, count = 0;
void setup() {
  Serial.begin(115200);
  pinMode(l, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  digitalWrite(c, LOW);
  digitalWrite(l, LOW);
}


void loop() {
  if (Serial.available() > 0) {
    char receChar = Serial.read();
    if (receChar != '\n') {
      receData += receChar;
    } else {
      int posi = receData.indexOf(':');
      dispData = receData.substring(0, posi).toInt();
      interval = receData.substring(posi + 1).toInt();
      if (dispData && interval) {
        Serial.printf("Data:%d -- Interval:%d \n", dispData, interval);
      }
      receData = "";
      flag = 0;
    }
  }
  if (flag) {
    for (int i = 0; i < 4; i++) {
      specialDigitDispaly(i + 1, arrayNum[i]);
    }
  }
  else {
    arrayNum[0] = dispData / 1000 % 10;
    arrayNum[1] = dispData / 100 % 10;
    arrayNum[2] = dispData / 10 % 10;
    arrayNum[3] = dispData % 10;

    if ((millis() - preTime) > interval) {
      count++;
      preTime = millis();
    }
    for (int i = 0; i < 4; i++)
      specialDigitDispaly(i + 1, arrayNum[(count + i) % 4]);
  }
}


void specialDigitDispaly(byte digit, byte number) {
  byte val = 0;
  val = bitSet(val, digit - 1);
  shiftOut(d, c, MSBFIRST, val);
  shiftOut(d, c, LSBFIRST, ~num[number]);
  digitalWrite(l, HIGH);
  digitalWrite(l, LOW);
}
