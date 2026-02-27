#include <Arduino.h> 
int threshold = 11; // Поріг спрацювання для сенсорних пінів
volatile unsigned int color = 1; // Змінна поточного режиму кольору (volatile для переривань)
volatile int brightness = 255; // Змінна поточної яскравості (від 0 до 255)
volatile unsigned long timer = 0; // Допоміжна змінна часу для обробки брязкоту дотику
volatile unsigned long changeLastTouch = 0; // Час останнього успішного перемикання кольору

void changeColor() { 
  timer = millis(); // Отримання поточного часу в мілісекундах

  if (timer - changeLastTouch > 200) { // Перевірка, чи минуло 200 мс (захист від хибних спрацювань)
    color++; // Перехід до наступного колірного режиму
    if (color > 4) color = 1; // Повернення до першого режиму, якщо значення перевищило 4
    changeLastTouch  = timer; // Оновлення часу останнього спрацювання
  }
} 

void brightnessHigh() { 
  brightness += 5; // Збільшення значення яскравості на 5 одиниць
  if (brightness > 255) brightness = 255; // Обмеження максимального значення яскравості до 255
} 

void brightnessLow() { 
  brightness -= 5; // Зменшення значення яскравості на 5 одиниць
  if (brightness < 0) brightness = 0; // Обмеження мінімального значення яскравості до 0
} 

void setup() { 
  pinMode(25, OUTPUT); // Встановлення 25-го піна (Red) як вихід
  pinMode(26, OUTPUT); // Встановлення 26-го піна (Green) як вихід
  pinMode(27, OUTPUT); // Встановлення 27-го піна (Blue) як вихід

  touchAttachInterrupt(4, changeColor, threshold); // Прив'язка зміни кольору до сенсорного піна 4
  touchAttachInterrupt(13, brightnessHigh, threshold); // Прив'язка збільшення яскравості до сенсорного піна 13
  touchAttachInterrupt(15, brightnessLow, threshold); // Прив'язка зменшення яскравості до сенсорного піна 15

  ledcSetup(0, 5000, 8); // Налаштування ШІМ-каналу 0: частота 5000 Гц, розрядність 8 біт
  ledcSetup(1, 5000, 8); // Налаштування ШІМ-каналу 1 для другого кольору
  ledcSetup(2, 5000, 8); // Налаштування ШІМ-каналу 2 для третього кольору
  ledcAttachPin(25, 0); // Прив'язка 25-го піна до ШІМ-каналу 0
  ledcAttachPin(26, 1); // Прив'язка 26-го піна до ШІМ-каналу 1
  ledcAttachPin(27, 2); // Прив'язка 27-го піна до ШІМ-каналу 2
} 

void selectColor() { 
  if (color == 1) { // Якщо обрано перший режим (Білий)
    ledcWrite(0, brightness); // Подати сигнал яскравості на канал 0 (Red)
    ledcWrite(1, brightness); // Подати сигнал яскравості на канал 1 (Green)
    ledcWrite(2, brightness); // Подати сигнал яскравості на канал 2 (Blue)
  }else if (color == 2) { // Якщо обрано другий режим (Червоний)
    ledcWrite(0, brightness); // Подати яскравість на червоний
    ledcWrite(1, 0); // Вимкнути зелений
    ledcWrite(2, 0); // Вимкнути синій
  }else if (color == 3) { // Якщо обрано третій режим (Зелений)
    ledcWrite(0, 0); // Вимкнути червоний
    ledcWrite(1, brightness); // Подати яскравість на зелений
    ledcWrite(2, 0); // Вимкнути синій
  }else if (color == 4) { // Якщо обрано четвертий режим (Синій)
    ledcWrite(0, 0); // Вимкнути червоний
    ledcWrite(1, 0); // Вимкнути зелений
    ledcWrite(2, brightness); // Подати яскравість на синій
  }
} 

void loop() { 
  selectColor(); // Постійний виклик функції оновлення стану світлодіода
} 