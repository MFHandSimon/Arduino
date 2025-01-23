const int l = 13, c = 14, d = 15;
byte COLdata, Rowdata;
int heartB[] = {0x99, 0x00, 0x00, 0x00, 0x81, 0xC3, 0xE7, 0xFF};
int heartS[] = {0xFF, 0xDB, 0x81, 0x81, 0xC3, 0xE7, 0xFF, 0xFF};
int black[] =  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
int kuang[] = {0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF};
unsigned long oldTime = 0;
int flag = 0;


void setup() {
  // put your setup code here, to run once:

  pinMode(l, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  digitalWrite(c, LOW);
  digitalWrite(l, LOW);
  analogSetWidth(10);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(2)) {
    for (int i = 0; i <= 8; i++) {
      Rowdata = 1 << i;
      COLdata = (black[i]);
      _display();
    }
    while (digitalRead(2)) {
      delay(20);

    }
    flag++;
    if (flag == 4) {
      flag = 1;
    }
  }

  for (int i = 0; i <= 7; i++) {
    Rowdata = 1 << i;
    if (flag == 0)  COLdata = ~(kuang[i]);
    if (flag == 1)  COLdata = ~(black[i]);
    if (flag == 2)  COLdata = (heartS[i]);
    if (flag == 3)  COLdata = (heartB[i]);
    _display();
  }
}

void _display() {
  shiftOut(d, c, MSBFIRST, COLdata);
  shiftOut(d, c, MSBFIRST, Rowdata);
  digitalWrite(l, HIGH);
  digitalWrite(l, LOW);
}
