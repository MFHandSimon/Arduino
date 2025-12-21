#include <Stepper.h>
Stepper mystepper(2048, 5, 19, 18, 23);
#define swPin 4
#define ledPin 12
int stepCount = 0;
bool SorN = 1;

void setup() {
  mystepper.setSpeed(10);
  Serial.begin(115200);
  pinMode(swPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(23, OUTPUT);
  while (1) {
    if (digitalRead(swPin) == HIGH) {
      break;
    }
  }
  digitalWrite(ledPin, HIGH);
  stepperControl(1024);
  digitalWrite(ledPin, LOW);
}

void loop() {
  if(Serial.available() > 0) {
    String receData = Serial.readStringUntil('\n');
    if(receData == "S2048") {
      digitalWrite(ledPin, HIGH);
      stepperControl(2048);
      digitalWrite(ledPin, LOW);
    }
    if(receData == "S-1024") {
      digitalWrite(ledPin, HIGH);
      SorN = 0;
      stepperzero();
      stepperControl(-1024);
      digitalWrite(ledPin, LOW);
    }
    if(receData == "C0.5") {
      digitalWrite(ledPin, HIGH);
      SorN = 1;
      stepperzero();
      stepperControl(1024);
      digitalWrite(ledPin, LOW);
    }
    if(receData == "P-1024") {
      digitalWrite(ledPin, HIGH);
      SorN = 0;
      stepperzero();
      digitalWrite(ledPin, LOW);
    }
  }
}

void stepperControl(int steps) {
  mystepper.step(steps);
  stepCount += steps;
}

void stepperzero(){
  stepCount %= 2048;
  if(stepCount != 0){
   if(SorN == 1){
    mystepper.step(1024);
    stepCount = 0;
   }else{
    mystepper.step(-1024);
    stepCount = 0;
   }
  }
}
