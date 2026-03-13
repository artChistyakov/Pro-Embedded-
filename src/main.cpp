#include <Arduino.h>
#include "BluetoothSerial.h"
#include "esp_bt_device.h"

BluetoothSerial SerialBT;

// Налаштування пінів
const int servoPin = 4;   // Пін для серво (Завдання 5)
const int buttonPin = 18; // Пін для кнопки (Завдання 4*)

// Змінні для кнопки (Завдання 4*)
volatile bool buttonFlag = false;

// Функція-обробник переривання для кнопки
void IRAM_ATTR handleButtonPress() {
  buttonFlag = true;
}

// Функція для отримання MAC-адреси (з твого коду)
void printDeviceAddress() {
  const uint8_t* point = esp_bt_dev_get_address();
  Serial.print("MAC Address: ");
  for (int i = 0; i < 6; i++) {
    char str[3];
    sprintf(str, "%02X", (int)point[i]);
    Serial.print(str);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
}

// Callback підключення (з твого коду)
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT) {
    Serial.println("Client Connected");
  }
}

void setup() {
  Serial.begin(115200);

  // Ініціалізація Bluetooth (Завдання 2)
  if (!SerialBT.begin("ESP32_Pro")) {
    Serial.println("An error occurred initializing Bluetooth");
  } else {
    Serial.println("Bluetooth initialized");
  }

  printDeviceAddress();
  SerialBT.register_callback(callback);
  SerialBT.setTimeout(10); // Невелика затримка для стабільного зчитування
}

void loop() {
  // 1. Відправка повідомлення з ПК на ТЕЛЕФОН (Слайд 28)
  if (Serial.available()) {
    String value = Serial.readString(); // Зчитуємо з монітора порту
    Serial.println("      Me: " + value);
    SerialBT.println(value);            // Відправляємо в Bluetooth
  }

  // 2. Приймання даних з ТЕЛЕФОНУ (Слайд 28)
  if (SerialBT.available()) {
    String valueStr = SerialBT.readString(); // Зчитуємо те, що прислав Android
    Serial.println("Android: " + valueStr);
  }
  
  // Прибери delay(1000)! Перевірка має бути миттєвою.
}