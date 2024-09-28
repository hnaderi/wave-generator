#include "application.h"
#include "pins_arduino.h"
#include "screen.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <RotaryEncoder.h>
#include <SPI.h>
#include <Wire.h>


#define ROTARY_P1 0
#define ROTARY_P2 1
RotaryEncoder encoder(ROTARY_P1, ROTARY_P2, RotaryEncoder::LatchMode::TWO03);
Application* app;

void checkPosition(){
  encoder.tick();
}

void setup() {
  Serial.begin(9600);

  Screen* screen = Screen::build();
  if (screen==nullptr) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  app = new Application(screen);

  pinMode(A1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ROTARY_P1), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_P2), checkPosition, CHANGE);
}


void loop() {
  static long lastPos = 0;

  if (digitalRead(A1) == LOW)
    app->onClick();

  int newPos = encoder.getPosition();
  if (newPos != lastPos) {
    app->onFreqChange(newPos - lastPos);
    lastPos = newPos;
  }

  app->tick();
}
