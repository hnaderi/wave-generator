#include "application.hpp"
#include "AD9833.h"
#include "data.hpp"
#include "screen.hpp"

Application *Application::build() {
  auto driver = new AD9833(SS, MISO, SCK);
  driver->begin();
  auto screen = Screen::build();
  const auto app = new Application(screen, driver);
  return app;
}

void Application::onFreqChange(long delta) {
  long percent = double(delta) * double(state.freq) / 100.0f;
  if (percent == 0)
    percent = delta > 0 ? 1 : -1;
  switch (state.selection) {
  case Selection::Normal:
    state.freq += percent;
    break;
  case Selection::Fast:
    state.freq += 10 * percent;
    break;
  case Selection::Precise:
    state.freq += delta;
    break;
  }

  state.freq = min(max(state.freq, 1), 12500000);

  updated = true;
}

void Application::onModChange(Mod mod) {
  state.mod = mod;
  updated = true;
}

void Application::onSelectionChange(long value) {
  const int delta = value > 0 ? +1 : -1;
  const int a = (state.selection + 3 + delta) % 3;
  state.selection = static_cast<Selection>(a);
  updated = true;
}

void Application::onWaveChange(long value) {
  const int delta = value > 0 ? +1 : -1;
  const int a = (state.wave + 3 + delta) % 3;
  state.wave = static_cast<Wave>(a);
  updated = true;
}

void Application::onClick(Click type) {
  if (type == Click::None)
    return;

  if (state.mod == Mod::Off)
    onModChange(Mod::On);
  else if (state.mod == Mod::On && type == Click::Long)
    onModChange(Mod::Off);
  else if (state.mod == Mod::On && type == Click::Short)
    onModChange(Mod::SettingWave);
  else if (state.mod == Mod::SettingWave && type == Click::Short)
    onModChange(Mod::SettingSelection);
  else if (state.mod == Mod::SettingSelection && type == Click::Short)
    onModChange(Mod::On);
  else if (type == Click::Long)
    onModChange(Mod::On);
}

void Application::onRotation(long value) {
  if (value == 0)
    return;
  switch (state.mod) {
  case Mod::On:
    onFreqChange(value);
    break;
  case Mod::SettingSelection:
    onSelectionChange(value);
    break;
  case Mod::SettingWave:
    onWaveChange(value);
    break;
  default:
    break;
  }
}

void Application::onUpdated() {
  if (state.mod == Mod::Off)
    driver->setWave(AD9833_OFF);
  else {
    driver->setFrequency(state.freq);
    switch (state.wave) {
    case Wave::Sine:
      driver->setWave(AD9833_SINE);
      break;
    case Wave::Rect:
      driver->setWave(AD9833_SQUARE1);
      break;
    case Wave::Tri:
      driver->setWave(AD9833_TRIANGLE);
      break;
    }
  }

  updated = false;
}

void Application::handle(InputEvent event) {
  onClick(event.click);
  onRotation(event.rotation);

  if (updated || state.mod > Mod::On)
    screen->render(state);

  if (updated)
    onUpdated();
}
