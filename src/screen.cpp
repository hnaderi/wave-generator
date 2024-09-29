#include "screen.hpp"
#include "data.hpp"
#include "error.h"
#include "icons.h"

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Screen *Screen::build() {
  Adafruit_SSD1306 *display =
      new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  if (display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    return new Screen(display);

  halt();
  return nullptr;
}

const char *freqFormat(long freq) {
  static char freqStr[11] = "----------";
  sprintf(freqStr, "%10ld", freq);
  return freqStr;
}

const void Screen::render(const State state) {
  using namespace data;

  display->clearDisplay();

  display->setTextColor(SSD1306_WHITE);
  display->cp437(true);
  display->setCursor(0, 0);

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
  display->drawBitmap(64 - 8, 0, icon, 16, 8, SSD1306_WHITE);
  display->setCursor(108, 0);
  switch (state.selection) {
  case Selection::Normal:
    display->write("1x");
    break;
  case Selection::Fast:
    display->write("10x");
    break;
  case Selection::Range:
    display->write("*10");
    break;
  }

  display->setCursor(0, 8);
  display->setTextSize(2);
  display->write(freqFormat(state.freq));

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

  display->setCursor(108, 24);
  display->write("Hz");

  display->display();
}
