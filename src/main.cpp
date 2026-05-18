#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>

// ============ НАЛАШТУВАННЯ МЕРЕЖІ ============
const char* ssid = "Lana";
const char* password = "0506153641";

// Заміни 192.168.X.X на реальну адресу твоєї камери!
// Зверни увагу: в кінці обов'язково має бути /jpg
const String streamUrl = "http://192.168.1.196/control?still=1"; 
// =============================================

TFT_eSPI tft = TFT_eSPI();
uint8_t* jpgBuffer;
const int maxJpgSize = 65536; // 64 КБ буфер для кадру (більше ніж достатньо для 320x240)

// Ця функція малює розпаковані шматочки JPEG на екрані
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
  if (y >= tft.height()) return 0;
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}

void setup() {
  Serial.begin(115200);

  // Налаштування екрана
  tft.begin();
  tft.setRotation(1); // Горизонтальна орієнтація
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("Connecting to WiFi...");

  // Налаштування JPEG декодера
  TJpgDec.setJpgScale(1);
  TJpgDec.setSwapBytes(true);
  TJpgDec.setCallback(tft_output);

  // Виділяємо пам'ять під кадр
  jpgBuffer = (uint8_t*)malloc(maxJpgSize);

  // Підключення до Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(10, 10);
  tft.println("Connected!");
  tft.println("Waiting for video...");
}

void loop() {
  // Якщо Wi-Fi працює - завантажуємо кадр
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(streamUrl);
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
      int len = http.getSize();
      
      // Якщо кадр не порожній і влазить в нашу пам'ять
      if (len > 0 && len <= maxJpgSize) {
        WiFiClient* client = http.getStreamPtr();
        int bytesRead = client->readBytes(jpgBuffer, len);
        
        // Якщо скачали весь кадр успішно - малюємо його!
        if (bytesRead == len) {
          TJpgDec.drawJpg(0, 0, jpgBuffer, len);
        }
      }
    } else {
      Serial.printf("HTTP Error: %d\n", httpCode);
    }
    http.end();
  }
}