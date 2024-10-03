#ifndef INPUTS_H_
#define INPUTS_H_

#include "RotaryEncoder.h"
#include "application.hpp"
#include "data.hpp"

using namespace data;

class Knob {
  RotaryEncoder *encoder;
  int pin1, pin2;
  long lastPos = 0;
  Knob(RotaryEncoder *encoder);

public:
  static Knob *build(int pin1, int pin2);
  long emit();
};

class Button {
  const uint8_t pin;
  const int high;
  unsigned long firstDown, startedWaiting;
  boolean clicked = false, waiting = false;

public:
  Button(uint8_t pin, boolean pullUp = true);
  Click emit();
};

class Input {
  Button *button;
  Knob *knob;
  Application *app;
  Input(Button *button, Knob *knob) : button(button), knob(knob) {}

public:
  struct Pins {
    int clk, dt, sw;
  };

  Input(Application *app, Pins pins)
      : button(new Button(pins.sw)), knob(Knob::build(pins.dt, pins.clk)),
        app(app) {}

  void tick() {
    app->handle({.click = button->emit(), .rotation = knob->emit()});
  }
};

#endif // INPUTS_H_
