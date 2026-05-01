#include "BluetoothSerial.h"
#include "esp_bt_device.h"

BluetoothSerial SerialBT;

void printDeviceAddress() {
  const uint8_t* point = esp_bt_dev_get_address();

  for (int i = 0; i < 6; i++) {
    char str[3];
    sprintf(str, "%02X", (int)point[i]);
    Serial.print(str);

    if (i < 5) {
      Serial.print(":");
    } else {
      Serial.print("\n");
    }
  }
}
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT) {
    Serial.println("Client Connected");
  }
}

int threshold = 30;


volatile unsigned long button_time = 0;


volatile unsigned long last_button1_time = 0;
void getTouch1() {
  button_time = millis();
  if (button_time - last_button1_time > 250)
  {
    SerialBT.println("1");
    Serial.println("Touched 1");
    last_button1_time = button_time;
  }
}

volatile unsigned long last_button2_time = 0;
void getTouch2() {
  button_time = millis();
  if (button_time - last_button2_time > 250)
  {
    SerialBT.println("2");
    Serial.println("Touched 2");
    last_button2_time = button_time;
  }
}

volatile unsigned long last_button3_time = 0;
void getTouch3() {
  button_time = millis();
  if (button_time - last_button3_time > 250)
  {
    SerialBT.println("3");
    Serial.println("Touched 3");
    last_button3_time = button_time;
  }
}

volatile unsigned long last_button4_time = 0;
void getTouch4() {
  button_time = millis();
  if (button_time - last_button4_time > 250)
  {
    SerialBT.println("4");
    Serial.println("Touched 4");
    last_button4_time = button_time;
  }
}

volatile unsigned long last_button5_time = 0;
void getTouch5() {
  button_time = millis();
  if (button_time - last_button5_time > 250)
  {
    SerialBT.println("5");
    Serial.println("Touched 5");
    last_button5_time = button_time;
  }
}

volatile unsigned long last_button6_time = 0;
void getTouch6() {
  button_time = millis();
  if (button_time - last_button6_time > 250)
  {
    SerialBT.println("6");
    Serial.println("Touched 6");
    last_button6_time = button_time;
  }
}

volatile unsigned long last_button7_time = 0;
void getTouch7() {
  button_time = millis();
  if (button_time - last_button7_time > 250)
  {
    SerialBT.println("7");
    Serial.println("Touched 7");
    last_button7_time = button_time;
  }
}

void setup() {
  Serial.begin(115200);

  if (!SerialBT.begin("ESP32")) {
    Serial.println("An error occurred initializing Bluetooth");
  } else {
    Serial.println("Bluetooth initialized");
  }
  printDeviceAddress();
  SerialBT.register_callback(callback);
  SerialBT.setTimeout(0);

  touchAttachInterrupt(4, getTouch1, threshold);
  touchAttachInterrupt(12, getTouch2, threshold);
  touchAttachInterrupt(13, getTouch3, threshold);
  touchAttachInterrupt(14, getTouch4, threshold);
  touchAttachInterrupt(27, getTouch5, threshold);
  touchAttachInterrupt(32, getTouch6, threshold);
  touchAttachInterrupt(33, getTouch7, threshold);
}

void loop() {
  delay(1000);
}
