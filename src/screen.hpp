#ifndef SCREEN_H_
#define SCREEN_H_

#include "Adafruit_SSD1306.h"
#include "data.hpp"

using data::State;

class Screen {
  Screen(Adafruit_SSD1306 *display) : display(display) {}
  Adafruit_SSD1306 *display;
  unsigned long blinked;

public:
  static Screen *build();
  const void render(const State state);
};

#endif // SCREEN_H_
