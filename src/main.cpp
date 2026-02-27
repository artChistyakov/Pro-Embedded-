#include <Arduino.h>    
int threshold = 11;     // Встановлення порогового значення для спрацьовування сенсорів
int touchValue;         // Оголошення змінної для зберігання значень сенсора
bool isReleased = true; // Прапор для відстеження стану відпускання сенсора
void getTouch1();       // Попереднє оголошення функції-обробника для першого сенсора
void getTouch2();       // Попереднє оголошення функції-обробника для другого сенсора
void getTouch3();       // Попереднє оголошення функції-обробника для третього сенсора

void setup() {                                                 \
  Serial.begin(115200);                           
  touchAttachInterrupt(4, getTouch1, threshold);  // Прив'язка переривання до сенсорного піна 4 з викликом функції getTouch1
  touchAttachInterrupt(13, getTouch2, threshold); // Прив'язка переривання до сенсорного піна 13 з викликом функції getTouch2
  touchAttachInterrupt(15, getTouch3, threshold); // Прив'язка переривання до сенсорного піна 15 з викликом функції getTouch3
} 

void getTouch1() {                              
  Serial.println("Touched 1"); // Вивід повідомлення про дотик до сенсора 1 у монітор порту
} 

void getTouch2() {                             
  Serial.println("Touched 2"); // Вивід повідомлення про дотик до сенсора 2 у монітор порту
} 

void getTouch3() {                             
  Serial.println("Touched 3"); // Вивід повідомлення про дотик до сенсора 3 у монітор порту
} 

void loop() {             
  delay(1000); // Затримка на 1000 мілісекунд (основна логіка працює через переривання)
} 