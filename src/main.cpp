#include <Arduino.h>
int threshold = 11;
int touchValue;
bool isReleased = true;

void setup() {
  Serial.begin(115200);
}

void loop() {
 touchValue = touchRead(4);

 if (touchValue <= threshold && isReleased) {
  Serial.println("Pin touched");
  isReleased = false;
 } else if (touchValue > threshold && !isReleased) {
  Serial.println("Pin released");
  isReleased = true;
 }
}

