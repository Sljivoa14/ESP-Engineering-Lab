#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 4
#define OLED_SCL 15

#define OLED_RESET -1

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("OLED TEST START");

    Wire.begin(OLED_SDA, OLED_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED NOT FOUND");
        while (true) {
            delay(1000);
        }
    }

    Serial.println("OLED FOUND!");

    // TEST 1: entire screen WHITE
    display.clearDisplay();
    display.fillScreen(SSD1306_WHITE);
    display.display();

    Serial.println("SCREEN SHOULD BE WHITE");

    delay(6000);

    // TEST 2: entire screen BLACK
    display.clearDisplay();
    display.display();

    Serial.println("SCREEN SHOULD BE BLACK");

    delay(1000);

    // TEST 3: TEXT
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("HELLO");

    display.setTextSize(1);
    display.setCursor(0, 30);
    display.println("ESP32 OLED");

    display.display();

    Serial.println("TEXT DRAW COMPLETE");
}

void loop() {
}


/*

ESP32
  │
  ├── firmware boots       ✅
  ├── Wire/I²C works       ✅
  ├── device at 0x3C       ✅
  ├── SSD1306 init         ✅
  ├── framebuffer writes   ✅
  ├── display() executes   ✅
  │
  └── PHYSICAL IMAGE       ❌

*/