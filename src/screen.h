#ifndef SCREEN_H_
#define SCREEN_H_

#include "Adafruit_SSD1306.h"
#include "data.hpp"
#include "icons.h"

using namespace data;

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

class Screen {
public:
  static Screen *build() {
    Adafruit_SSD1306 *display =
        new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

    if (display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
      return new Screen(display);

    return nullptr;
  }

  const void render(const State state) {
    display->clearDisplay();

    display->setTextColor(SSD1306_WHITE);
    display->cp437(true);

    const unsigned char *icon;
    switch (state.wave) {
    case data::Wave::Rect:
      icon = RECT_ICON;
      break;
    case data::Wave::Sine:
      icon = SINE_ICON;
      break;
    case data::Wave::Tri:
      icon = TRI_ICON;
      break;
    }
    display->drawBitmap(64 - 8, 0, icon, 16, 8, SSD1306_WHITE);
    display->setCursor(108, 0);
    display->write("1x");

    display->setCursor(0, 8);
    display->setTextSize(2);
    display->write(freqFormat(state.freq));

    display->setCursor(0, 24);
    display->setTextSize(1);
    display->write("=ON=");


    display->setCursor(108, 24);
    display->write("Hz");

    display->display();
  }

private:
  Screen(Adafruit_SSD1306 *display) : display(display) {}
  Adafruit_SSD1306 *display;

  const char *freqFormat(long freq) {
    static char freqStr[11] = "----------";
    sprintf(freqStr, "%10ld", freq);
    return freqStr;
  }
};

#endif // SCREEN_H_
