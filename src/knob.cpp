#include "RotaryEncoder.h"
#include "inputs.hpp"

Knob::Knob(RotaryEncoder *encoder) : encoder(encoder) {}

long Knob::emit() {
  int newPos = encoder->getPosition();
  if (newPos != lastPos) {
    const auto delta = newPos - lastPos;
    lastPos = newPos;
    return delta;
  }
  return 0;
}

static RotaryEncoder *_encoder;
static Knob *_attachedKnob = nullptr;
void _checkPosition() { _encoder->tick(); }

Knob *Knob::build(int pin1, int pin2) {
  _encoder = new RotaryEncoder(pin1, pin2, RotaryEncoder::LatchMode::TWO03);
  attachInterrupt(digitalPinToInterrupt(pin1), _checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin2), _checkPosition, CHANGE);
  _attachedKnob = new Knob(_encoder);
  return _attachedKnob;
}
