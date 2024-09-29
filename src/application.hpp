#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "AD9833.h"
#include "Arduino.h"
#include "data.hpp"
#include "screen.hpp"

using namespace data;

class Application {
  Screen *screen;
  AD9833 driver;
  State state;
  boolean requiresRendering = true;

  void onFreqChange(long delta);
  void onModChange(Mod mod);
  void onClick(Click type);

public:
  Application(Screen *screen) : screen(screen), driver(AD9833(10)) {}
  void handle(InputEvent event);
};

#endif // APPLICATION_H_
