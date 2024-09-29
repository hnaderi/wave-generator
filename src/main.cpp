#include "application.hpp"
#include "inputs.hpp"
#include <Arduino.h>

Application *app;
Input *input;

void setup() {
  app = Application::build();
  input = new Input(app, {.clk = 0, .dt = 1, .sw = A1});
}

void loop() { input->tick(); }
