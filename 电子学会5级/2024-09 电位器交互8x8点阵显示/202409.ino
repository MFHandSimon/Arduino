const int potPin = A0, swPin = 2, l = 18, c = 19, d = 23;  //potPin为电位器 swPin为按键
byte dataRow, dataCol;                                     //行，列
bool displayFlag = 1;                                      //扫描的模式
int count = 0;                                             //当前的位置

void setup() {
  pinMode(swPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(l, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  analogSetWidth(9);
  for (int i = 0; i <= 7; i++) {  //点阵黑屏
    dataRow = 1 << i;
    dataCol = ~(0);
    matrixDisplay();
  }
  while (1) {  //等待按键按下进入loop函数
    if (digitalRead(swPin)) {
      break;
    }
  }
}

void loop() {
  int potVal = analogRead(potPin);  //定义电位器值变量
  int swVal = digitalRead(swPin);   //定义按键状态变量
  int curRow;
  if (swVal) {                      //按键按下
    displayFlag = !displayFlag;     //切换 单光点or线 扫描
    delay(100);                     //防抖
  }
  curRow = count % 8;
  dataRow = 0;
  bitSet(dataRow, (7 - curRow));
  count++;

  if (displayFlag) {  //进入单光电扫描模式
    dataCol = 0;      //整列清空
    matrixDisplay();
    delay(potVal);
  }
  if (!displayFlag) {               //进入线扫描模式
    for (int i = 7; i >= 0; i--) {  //遍历8列
      dataCol = 0xff;               //将列设为低
      bitClear(dataCol, i);         //点亮这一列的8个LED
      matrixDisplay();
      delay(potVal);
    }
  }
}

void matrixDisplay() {
  shiftOut(d, c, LSBFIRST, dataCol);
  shiftOut(d, c, LSBFIRST, dataRow);
  digitalWrite(l, HIGH);
  digitalWrite(l, LOW);
}
