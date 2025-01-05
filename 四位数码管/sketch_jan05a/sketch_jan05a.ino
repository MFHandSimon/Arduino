void specialDigitDispaly(byte digit, byte num) {
  byte val = 0;
  val = bitSet(val, digit - 1);
  shiftOut(dataPin, clockPin, MSBFIRST, val);   //将一个字节（8 位）的数据按照指定的顺序和时序，从一个数据引脚逐位输出到另一个时钟引脚
  shiftOut(dataPin, clockPin, LSBFIRST, ~NUM[num]);   
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
}
