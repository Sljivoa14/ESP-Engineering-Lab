/*
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 21
#define OLED_SCL 22



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void showSystemStatus() {
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("ESP ENGINEERING LAB");

    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

    display.setCursor(0, 15);
    display.print("CPU: ");
    display.print(getCpuFrequencyMhz());
    display.println(" MHz");

    display.setCursor(0, 26);
    display.print("HEAP: ");
    display.print(ESP.getFreeHeap() / 1024);
    display.println(" KB");

    display.setCursor(0, 37);
    display.print("FLASH: ");
    display.print(ESP.getFlashChipSize() / (1024 * 1024));
    display.println(" MB");

    display.setCursor(0, 48);
    display.print("WIFI: ");
    display.println(WiFi.status() == WL_CONNECTED ? "CONNECTED" : "OFFLINE");

    display.setCursor(0, 58);
    display.println("[ SYSTEM READY ]");

    display.display();
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("OLED TEST START");

    Wire.begin(OLED_SDA, OLED_SCL);

    Serial.println("Using SDA = 21");
    Serial.println("Using SCL = 22");

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED NOT FOUND!");

        while (true) {
            delay(1000);
        }
    }

    Serial.println("OLED FOUND!");

    // WHITE SCREEN
    display.clearDisplay();
    display.fillScreen(SSD1306_WHITE);
    display.display();

    Serial.println("WHITE SCREEN");
    delay(3000);

    // TEXT TEST
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("COLeGiO SM");

    display.setTextSize(1);
    display.setCursor(0, 30);
    display.println("ESP32 OLED");
    display.println("TEST SUCCESS");

    display.display();

    Serial.println("TEXT DRAW COMPLETE");
}

void loop() {
}




OLED SCREEN WORKS

OLED CAMERA [WORKING ON IT]

A NEW FILE STRUCTRE:
│
├── ESP-Engineering-Lab-WROOM/
│   ├── platformio.ini
│   └── src/
│       └── main.cpp
│
└── ESP-Engineering-Lab-Camera/
    ├── platformio.ini
    └── src/
        └── main.cpp     <-    FRAME CAPTURE WORKS !!!
                                NEXT PART: CONECTNING THE ESPWROOM WITH THE ESP32S3


NETWORK LAB
    │
    ├── Wi-Fi scanner
    ├── IP information
    ├── signal strength
    └── network diagnostics
          ↓
CYBERSECURITY LAB
    │
    ├── device/network inventory
    ├── service diagnostics
    ├── packet/network telemetry
    └── defensive security experiments
          ↓
ESP ENGINEERING LAB
    │
    ├── OLED UI
    ├── buttons/input
    ├── sensors
    ├── camera
    └── modular applications



┌────────────────┐
│ ESP ENGINEERING│
│                │
│ CPU: 240 MHz   │
│ HEAP: 287 KB   │
│ PSRAM: 8 MB    │
│ WiFi: OFF      │
│                │
│ [SYSTEM READY] │
└────────────────┘

*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 21
#define OLED_SCL 22

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Example 32x32 bitmap
const unsigned char globeBitmap[] PROGMEM = {
  0x00,0x00,0x00,0x00,
  0x00,0x7E,0x00,0x00,
  0x01,0xFF,0x80,0x00,
  0x03,0xC3,0xC0,0x00,
  0x07,0x81,0xE0,0x00,
  0x0F,0x00,0xF0,0x00,
  0x1E,0x00,0x78,0x00,
  0x3C,0x00,0x3C,0x00,
  0x78,0x00,0x1E,0x00,
  0x70,0x00,0x0E,0x00,
  0x60,0x00,0x06,0x00,
  0x60,0x00,0x06,0x00,
  0x60,0x00,0x06,0x00,
  0x70,0x00,0x0E,0x00,
  0x78,0x00,0x1E,0x00,
  0x3C,0x00,0x3C,0x00,
  0x1E,0x00,0x78,0x00,
  0x0F,0x00,0xF0,0x00,
  0x07,0x81,0xE0,0x00,
  0x03,0xC3,0xC0,0x00,
  0x01,0xFF,0x80,0x00,
  0x00,0x7E,0x00,0x00
};

void setup() {
  Serial.begin(115200);

  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED NOT FOUND!");
    while (true) delay(1000);
  }

  display.clearDisplay();

  // Draw the mini picture in the center
  display.drawBitmap(
    42, 22,          // X, Y position
    globeBitmap,
    80, 52,          // width, height
    SSD1306_WHITE
  );

  display.display();
}

void loop() {
}