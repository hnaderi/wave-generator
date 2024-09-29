#include "Arduino.h"
#include "data.hpp"
#include "inputs.hpp"

#define LONG_CLICK_TIME 750
#define MIN_CLICK_TIME 150

Button::Button(uint8_t pin, boolean pullUp)
    : pin(pin), high(pullUp ? LOW : HIGH) {
  const auto mode = pullUp ? INPUT_PULLUP : INPUT;
  pinMode(pin, mode);
}

Click Button::emit() {
  const boolean value = digitalRead(pin) == high;
  const auto now = millis();

  if (!clicked) {
    if (value) {
      clicked = true;
      firstDown = now;
    }
  } else {
    if (!value) {
      if (!waiting) {
        startedWaiting = now;
        waiting = true;
      } else {
        const auto waited = now - startedWaiting;
        if (waited > MIN_CLICK_TIME) {
          clicked = false;
          waiting = false;
          const auto duration = now - firstDown;
          if (duration > LONG_CLICK_TIME)
            return data::Click::Long;
          else
            return data::Click::Short;
        }
      }
    }
  }

  return data::Click::None;
}
