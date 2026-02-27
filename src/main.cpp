#include <Arduino.h>
int threshold = 11;
int touchValue;
bool isReleased = true;

void getTouch1();
void getTouch2();
void getTouch3();

void setup() {
  Serial.begin(115200);
  touchAttachInterrupt(4, getTouch1, threshold);
  touchAttachInterrupt(13, getTouch2, threshold);
  touchAttachInterrupt(15, getTouch3, threshold);
}

void getTouch1() {
  Serial.println("Touched 1");
}

void getTouch2() {
  Serial.println("Touched 2");
}

void getTouch3() {
  Serial.println("Touched 3");
}



void loop() {
  delay(1000);
}

