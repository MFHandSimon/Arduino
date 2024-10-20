// int keyVal, keyPin, preKeyVal, nowTime, oldtime, settime = 20, preKeyState;      把我放到第一行

//消抖
void getKeyState() {
  keyVal = digitalRead(keyPin);
  if (keyVal != preKeyVal) {
    nowTime = millis();
  }
  preKeyVal = keyVal;;
  if (nowTime - oldtime >= stetime) {
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
