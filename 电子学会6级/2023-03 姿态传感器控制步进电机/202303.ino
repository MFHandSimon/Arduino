#include <AccelStepper.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
const int in1 = 5, in2 = 18, in3 = 19, in4 = 23;
const int stepMode = 8;
const int threshold = 20;
const int touchPin = T0;
bool touchDetected = false;
bool touch1done = false;
bool touch2done = false;
bool unmoveed = true;
int touchnumber = 0;
AccelStepper stepper(stepMode, in1, in3, in2, in4);
MPU6050 mpu6050(Wire);

void setup() {
  touchAttachInterrupt(touchPin, touchDoing, threshold);
  stepper.setMaxSpeed(800);
  stepper.setAcceleration(50.0);
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  while (unmoveed) {
    Touch();
    if (touchnumber == 1 && !touch1done) {
      run(1024);
      run(0);
      touch1done = true;
    } else if (touchnumber == 3 && !touch2done) {  //至于问什么是3而不是2,别问，特性
      run(-1024);
      run(0);
      touch2done = true;
      unmoveed = false; 
    }
  }
  getGyro();
}

void run(int steps) {
  stepper.moveTo(steps);
  while (stepper.distanceToGo() != 0) {
    Serial.println(stepper.currentPosition());
    stepper.run();
  }
}

void touchDoing() {
  touchDetected = true;
}

void Touch() {
  Serial.println(touchnumber);
  int touchValue = touchRead(touchPin);
  Serial.print("Touch Value: ");
  Serial.println(touchValue);
  if (touchDetected) {
    Serial.println("Touch detected!");
    touchDetected = false;
    touchnumber++;
    delay(300);
  }
}

void getGyro() {
  mpu6050.update();
  Serial.print("only gyro: ");
  Serial.println(mpu6050.getGyroX());
  if (mpu6050.getGyroX() > 45 && mpu6050.getGyroX() > -45) {
    run(0);
  }
  else if (mpu6050.getGyroX() > 90) {
    run(1024);
  } else if (mpu6050.getGyroX() < -90) {
    run(-1024);
  }
}