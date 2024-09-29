#include "error.h"
#include "Arduino.h"
#include "avr/interrupt.h"
#include "pins_arduino.h"

void halt() {
  cli();
  pinMode(LED_BUILTIN, OUTPUT);
  while (1) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
}
