#ifndef SCREEN_H_
#define SCREEN_H_

#include "Adafruit_SSD1306.h"
#include "data.hpp"

using data::State;

class Screen {
public:
  static Screen *build();
  const void render(const State state);

private:
  Screen(Adafruit_SSD1306 *display) : display(display) {}
  Adafruit_SSD1306 *display;
};

#endif // SCREEN_H_
