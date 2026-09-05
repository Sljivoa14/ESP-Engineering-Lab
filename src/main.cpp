#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define LCD_MOSI 23
#define LCD_SCLK 18
#define LCD_CS   15
#define LCD_DC   2
#define LCD_RST  4
#define LCD_BLK   32

Adafruit_ST7789 lcd(LCD_CS, LCD_DC, LCD_RST);

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Backlight
    pinMode(LCD_BLK, OUTPUT);
    digitalWrite(LCD_BLK, HIGH);

    // Initialize SPI
    SPI.begin(LCD_SCLK, -1, LCD_MOSI, LCD_CS);

    // Initialize the 170x320 ST7789
    lcd.init(170, 320);

    lcd.setRotation(1);
    lcd.fillScreen(ST77XX_BLACK);

    lcd.setTextColor(ST77XX_WHITE);
    lcd.setTextSize(2);
    lcd.setCursor(10, 20);
    lcd.println("HELLO!");

    Serial.println("DISPLAY TEST COMPLETE");
}

void loop() {
}