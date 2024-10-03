#include "application.hpp"
#include "inputs.hpp"
#include <Arduino.h>

Application *app;
Input *input;

void setup() {
  app = Application::build();
  input = new Input(app, {.clk = 2, .dt = 3, .sw = 6});
}

void loop() { input->tick(); }
