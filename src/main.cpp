#include <Arduino.h>
unsigned long int timer;


void setup() {
  Serial.begin(115200);
  timer = millis();
}

void loop() {
  if (millis() -  timer >= 100) {
    Serial.println("Touch value:" + (String)touchRead(4));
    timer = millis();
  }
}

