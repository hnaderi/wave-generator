#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "AD9833.h"
#include "Arduino.h"
#include "data.hpp"
#include "screen.hpp"

using namespace data;

class Application {
  Screen *screen;
  AD9833 *driver;
  State state;
  boolean updated = true;

  void onFreqChange(long delta);
  void onModChange(Mod mod);
  void onSelectionChange(long value);
  void onWaveChange(long value);

  void onClick(Click type);
  void onRotation(long value);

  void onUpdated();

  Application(Screen *screen, AD9833 *driver)
      : screen(screen), driver(driver) {}

public:
  static Application *build();
  void handle(InputEvent event);
};

#endif // APPLICATION_H_
