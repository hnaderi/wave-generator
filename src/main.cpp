#include <icons.h>
#include <AD9833.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
AD9833 fgen(10);

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.cp437(true);

  display.drawBitmap(16, 0, RECT_ICON, 16, 8, SSD1306_WHITE);
  display.drawBitmap(64 - 8, 0, SINE_ICON, 16, 8, SSD1306_WHITE);
  display.drawBitmap(128 - 16 - 16, 0, TRI_ICON, 16, 8, SSD1306_INVERSE);

  display.setCursor(0, 8);
  display.setTextSize(2);
  display.write("12,500,000");

  display.setCursor(108, 24);
  display.setTextSize(1);
  display.write("Hz");

  display.display();
}

void loop() {
  // // Invert and restore display, pausing in-between
  // display.invertDisplay(true);
  // delay(1000);
  // display.invertDisplay(false);
  // delay(1000);
}
