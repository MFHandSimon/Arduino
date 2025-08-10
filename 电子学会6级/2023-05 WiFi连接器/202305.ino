#include <WiFi.h>
String ssid = "";
String password = "";
const int buttonPin = 4;
bool flag = false;   


void setup() {
  // put your setup code here, to run once:积智时间机器人 3F-1
    Serial.begin(115200);
         
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!flag && digitalRead(buttonPin) == 1){
    flag = true;
    connectWiFi();
  }

}

void connectWiFi(){ 
    Serial.print("\n输入 SSID: ");
    while(true){
      if(Serial.available()){
        ssid = Serial.readString();
        Serial.print(ssid);
        break;
      }
    }
    Serial.print("\n输入 Password: ");
    while(true){
      if(Serial.available()){
        password = Serial.readString();
        Serial.print(password);
        break;
      }
    }
    WiFi.begin(ssid, password);
    Serial.print("\n");
    while(WiFi.status()!=WL_CONNECTED){
      delay(500);
      Serial.print('.');
    }
    Serial.print(WiFi.localIP());
    flag = false;
}

// Serial.available();