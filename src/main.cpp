#include <Arduino.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

BluetoothSerial BT;

const int LED = 2, ledPwm = 13;
int value;

void setup(){
  Serial.begin(115200);
  BT.begin("ESP32test");
  pinMode(LED, OUTPUT);
  pinMode(ledPwm, OUTPUT);
}

void loop(){
  if (BT.available()){
    String incoming = BT.readString();
    char type = incoming[0];
    switch (type){
    case 'B':
      digitalWrite(LED, !digitalRead(LED));
      break;
    case 'S':
      value = incoming.substring(1, sizeof(incoming) - 1).toInt();
      analogWrite(ledPwm, value);
      break;
    /*
    case 'D':
      int lecturaPot = analogRead(pot);
      int temp = map(lecturaPot, 0, 4095, -20, 120);
      BT.write(temp);
      break;
   */
    default:
      break;
    }
  }
}