#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <DHT.h>

const char* ssid = "Lana";           // Твій Wi-Fi
const char* password = "0506153641"; // Твій пароль


DHT dht(13, DHT11);

// Створюємо асинхронний сервер на 80 порту
AsyncWebServer server(80);

// --- МАГІЧНА ФУНКЦІЯ ЗАМІНИ ТЕКСТУ ---
// Коли сервер надсилає HTML файл, він шукає слова між символами %...%
// і замінює їх на те, що поверне ця функція.
String processor(const String& var) {
  if (var == "TEMPERATURE") {
    float t = dht.readTemperature();
    if (isnan(t)) return "Error";
    return String(t, 1); // 1 знак після коми
  }
  else if (var == "HUMIDITY") {
    float h = dht.readHumidity();
    if (isnan(h)) return "Error";
    return String(h, 1);
  }
  return String(); // Якщо нічого не знайшли, повертаємо порожнечу
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  // 1. Запускаємо файлову систему (нашу "флешку")
  if (!SPIFFS.begin(true)) {
    Serial.println("Помилка монтування SPIFFS!");
    return;
  }

  // 2. Підключаємося до Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Підключення до Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nПідключено! IP адреса:");
  Serial.println(WiFi.localIP());

  // 3. НАЛАШТУВАННЯ МАРШРУТІВ СЕРВЕРА 
  server.on("/", HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/style.css", HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/temp.png", HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/temp.png", "image/png");
  });

  server.begin();
  Serial.println("Асинхронний сервер запущено!");
}

void loop() {
  // Асинхронний сервер працює сам у фоні на перериваннях.
  // loop() залишається абсолютно порожнім! Ти можеш додати сюди будь-що інше.
}