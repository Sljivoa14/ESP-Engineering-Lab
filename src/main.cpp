#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 3
#define OLED_SCL 22

/*
#define OLED_RESET -1

#define SDA_PIN 21
#define SCL_PIN 22*/

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("================================");
    Serial.println("OLED TEST START");
    Serial.println("SDA = GPIO3");
    Serial.println("SCL = GPIO22");
    Serial.println("================================");

    Wire.begin(OLED_SDA, OLED_SCL);

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

    // BLACK SCREEN
    display.clearDisplay();
    display.display();

    Serial.println("BLACK SCREEN");
    delay(1000);

    // TEXT TEST
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("HELLO!");

    display.setTextSize(1);
    display.setCursor(0, 30);
    display.println("ESP32 OLED");
    display.println("TEST SUCCESS");

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