const int threshold = 40;
const int touchPin = T6;
bool touchDetected = false;
void touchDoing() {
  touchDetected = true;
}

void setup() {
 touchAttachInterrupt(touchPin, touchDoing, threshold);
}
void loop() {
  int touchValue = touchRead(touchPin);
  Serial.print("Touch Value: ");
  Serial.println(touchValue);
  if (touchDetected) {
    Serial.println("Touch detected!");
    touchDetected = false;
  }
  delay(200);
}