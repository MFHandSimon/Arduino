const int l = 13, c = 14, d = 15;
int keyVal, keyPin = 2, preKeyVal, nowTime, oldtime, settime = 20, preKeyState;
int number, first_time;
bool keyFlag = false;
const byte num[11] = {
  //  abcdefg.
  0b11111100,         //0
  0b01100000,         //1
  0b11011010,         //2
  0b11110010,         //3
  0b01100110,         //4
  0b10110110,         //5
  0b10111110,         //6
  0b11100000,         //7
  0b11111110,         //8
  0b11110110,         //9
  0b00000001          //.
};


void setup() {
  pinMode(l, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  digitalWrite(c, LOW);
  digitalWrite(l, LOW);
  analogSetWidth(10);
}








void loop() {
  getKeyState();
  if (keyFlag) {
    first_time = millis();

  } else {
    superdisplay(millis() - first_time);
    first_time = millis();
  }
}




void _display(int digit, int number) {
  byte i = 0;
  shiftOut(d, c, MSBFIRST, bitSet(i, digit - 1));
  shiftOut(d, c, LSBFIRST, ~num[number]);
  digitalWrite(l, HIGH);
  digitalWrite(l, LOW);
}



//消抖
void getKeyState() {
  keyVal = digitalRead(!keyPin);    //反向
  if (keyVal != preKeyVal) {
    nowTime = millis();
  }
  preKeyVal = keyVal;
  if (nowTime - oldtime >= settime) {
    oldtime = millis();
    if (keyVal != preKeyState) {
      preKeyState = keyVal;
      if (keyVal == HIGH) {
        keyFlag = !keyFlag;
        Serial.println(keyFlag);  //打印状态
      }
    }
  }
}

//显示
void superdisplay(int number) {
  int _superdisplay[4] {};
  _superdisplay[1] = number / 1000;
  _superdisplay[2] = number / 100 % 10;
  _superdisplay[3] = number / 10 % 10;
  _superdisplay[4] = number % 10;
  for (int i = 1; i <= 4; i++)    _display(i, _superdisplay[i]);
}
