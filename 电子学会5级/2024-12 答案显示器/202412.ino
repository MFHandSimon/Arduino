const int l = 13, c = 14, d = 15;
byte COLdata, Rowdata;
byte gou[] {0x00, 0x00, 0x80, 0x40, 0x22, 0x14, 0x08, 0x00};
byte cha[] {0x00, 0x00, 0x14, 0x08, 0x14, 0x00, 0x00, 0x00};
byte quan[] {0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF};
byte kong[] {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
int a_button = 16, b_button = 17;
unsigned long oldTime = 0;
bool flag = 1;


void setup() {
  // put your setup code here, to run once:

  pinMode(l, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  digitalWrite(c, LOW);
  digitalWrite(l, LOW);
  analogSetWidth(10);

}
void _display() {
  shiftOut(d, c, MSBFIRST, COLdata);
  shiftOut(d, c, MSBFIRST, Rowdata);
  digitalWrite(l, HIGH);
  digitalWrite(l, LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
  int a = !digitalRead(a_button);
  int b = !digitalRead(b_button);
  if (flag) {
    for (int i = 0; i <= 7; i++) {
      if (a || b) flag = false;
      Rowdata = 1 << i;
      COLdata = ~(quan[i]);
      _display();
    }
  }

  if (a && b) {
    for (int i = 0; i <= 7; i++) {
      Rowdata = 1 << i;
      COLdata = ~(quan[i]);
      _display();
    }
  } else  if (a) {
    for (int i = 0; i <= 7; i++) {
      Rowdata = 1 << i;
      COLdata = ~(gou[i]);
      _display();
    }
  } else if (b) {
    for (int i = 0; i <= 7; i++) {
      Rowdata = 1 << i;
      COLdata = ~(cha[i]);
      _display();
    }
  }
  else {
    for (int i = 0; i <= 7; i++) {
      Rowdata = 1 << i;
      COLdata = ~(kong[i]);
      _display();
    }
  }
}
