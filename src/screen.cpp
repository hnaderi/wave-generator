#include "screen.hpp"
#include "Arduino.h"
#include "data.hpp"
#include "error.h"
#include "icons.h"

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define BLINK_EVERY 500

Screen *Screen::build() {
  Adafruit_SSD1306 *display =
      new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  if (display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    return new Screen(display);

  halt();
  return nullptr;
}

const char *freqFormat(long freq) {
  static char freqStr[11];
  const byte points = freq >= 1e6 ? 2 : freq >= 1e3 ? 1 : 0;
  for (int i = 9; i >= 0; i--) {
    if (freq > 0) {
      if (points == 2 && i == 9 - 3)
        freqStr[i--] = ',';
      else if ((points == 1 && i == 9 - 3) || (points == 2 && i == 9 - 6 - 1))
        freqStr[i--] = '.';
      byte digit = freq % 10;
      freq /= 10;
      freqStr[i] = '0' + digit;
    } else {
      freqStr[i] = ' ';
    }
  }
  return freqStr;
}

const void Screen::render(const State state) {
  using namespace data;
  const auto now = millis();
  const auto startedBlinking = now - blinked;
  const auto blink = startedBlinking < BLINK_EVERY;
  if (!blink && startedBlinking > 2 * BLINK_EVERY)
    blinked = now;

  display->clearDisplay();

  display->setTextColor(SSD1306_WHITE);
  display->cp437(true);
  display->setTextSize(1);

  const unsigned char *icon;

  switch (state.wave) {
  case Wave::Rect:
    icon = RECT_ICON;
    break;
  case Wave::Sine:
    icon = SINE_ICON;
    break;
  case Wave::Tri:
    icon = TRI_ICON;
    break;
  }
  if (state.mod == Mod::SettingWave && blink) {
    display->setCursor(64 - 8 - 8, 0);
    display->write(">");
  }
  display->drawBitmap(64 - 8, 0, icon, 16, 8, SSD1306_WHITE);

  if (state.mod == Mod::SettingSelection && blink) {
    display->setCursor(100, 0);
    display->write(">");
  }

  display->setCursor(108, 0);
  switch (state.selection) {
  case Selection::Normal:
    display->write("1%");
    break;
  case Selection::Fast:
    display->write("10%");
    break;
  case Selection::Precise:
    display->write(".1");
    break;
  }

  display->setCursor(0, 24);
  display->setTextSize(1);

  switch (state.mod) {
  case Mod::On:
    display->write("=ON=");
    break;
  case Mod::Off:
    display->write("=OFF=");
    break;
  case Mod::SettingWave:
  case Mod::SettingSelection:
    display->write("=SET=");
    break;
  }

  display->setCursor(0, 8);
  display->setTextSize(2);
  display->write(freqFormat(state.freq));
  display->setTextSize(1);
  if (state.freq < 1e3) {
    display->setCursor(108, 24);
    display->write("Hz");
  } else {
    display->setCursor(107, 24);
    if (state.freq < 1e6)
      display->write("KHz");
    else
      display->write("MHz");
  }

  display->display();
}
