const int l = 13, c = 14, d = 15;
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
void _display(int digit, int number) {
  byte i = 0;
  shiftOut(d, c, MSBFIRST, bitSet(i, digit - 1));
  shiftOut(d, c, LSBFIRST, ~num[number]);
  digitalWrite(l, HIGH);
  digitalWrite(l, LOW);
}

void loop() {
//_display( 1,2 )    第一位显示2

}
