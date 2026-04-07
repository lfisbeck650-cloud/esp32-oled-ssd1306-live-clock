#include <WiFi.h>
#include <time.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Wi-Fi credentials
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// OLED display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR     0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// NTP server
const char* ntpServer = "pool.ntp.org";

// Time zone for Germany: CET/CEST
const char* tzInfo = "CET-1CEST,M3.5.0/2,M10.5.0/3";

void showTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Could not");
    display.println("load time");
    display.display();
    return;
  }

  char timeString[16];
  strftime(timeString, sizeof(timeString), "%H:%M:%S", &timeinfo);

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println(timeString);
  display.display();
}

void setup() {
  Serial.begin(115200);

  // I2C: SDA = GPIO22, SCL = GPIO21
  Wire.begin(22, 21);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 not found");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Starting...");
  display.display();

  WiFi.begin(ssid, password);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  display.display();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  setenv("TZ", tzInfo, 1);
  tzset();

  configTime(0, 0, ntpServer);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("NTP started");
  display.display();

  delay(1000);
}

void loop() {
  showTime();
  delay(1000);
}
