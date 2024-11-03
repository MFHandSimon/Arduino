const int l = 13, c = 14, d = 15;
byte COLdata, Rowdata;
int big[8] = {0x1E, 0x3F, 0x7F, 0xFE, 0xFE, 0x7F, 0x3F, 0x1E};
int small[8] = {0x00, 0x18, 0x3C, 0x78, 0x3C, 0x18, 0x00, 0x00};
int middle[8] =  {0x0C, 0x1E, 0x3E, 0x7C, 0x3E, 0x1E, 0x0C, 0x00};

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


  if (millis() - oldTime >= 1000) {
    oldTime = millis();
    flag++;
    if (flag == 4) {
      flag = 1;
    }
  }
  for (int i = 0; i <= 7; i++) {
    Rowdata = 1 << i;
    if (flag == 1)  COLdata = ~(small[i]);
    else if (flag == 2)  COLdata = ~(middle[i]);
    else if (flag == 3)  COLdata = ~(big[i]);
    _display();
  }
}

void _display() {
  shiftOut(d, c, MSBFIRST, COLdata);
  shiftOut(d, c, MSBFIRST, Rowdata);
  digitalWrite(l, HIGH);
  digitalWrite(l, LOW);
}
