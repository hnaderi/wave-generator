#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "AD9833.h"
#include "Arduino.h"
#include "data.hpp"
#include "screen.h"

using namespace data;

class Application {
public:
  Application(Screen* screen) : screen(screen), driver(AD9833(10)) {}

  void onFreqChange(long delta) {
    if (delta == 0)
      return;

    state.freq += delta;
    requiresRendering = true;

    if (state.mod == Mod::Setting)
      ;
  }
  void onClick() {
    if (!clicked)
      clicked = true;
    lastClick = millis();
  }

  void tick() {
    if (requiresRendering) {
      screen->render(state);
      requiresRendering = false;
    }
  }

private:
  Screen* screen;
  AD9833 driver;
  State state;

  boolean clicked = false;
  unsigned long lastClick = 0;

  boolean requiresRendering = true;
};

#endif // APPLICATION_H_
