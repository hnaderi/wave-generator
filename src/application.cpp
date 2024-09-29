#include "application.hpp"
#include "data.hpp"

void Application::onFreqChange(long delta) {
  switch (state.selection) {
  case Selection::Normal:
    state.freq += delta;
    break;
  case Selection::Fast:
    state.freq += delta * 10;
    break;
  case Selection::Range:
    state.freq *= 10;
    break;
  }

  requiresRendering = true;
}

void Application::onModChange(Mod mod) {
  state.mod = mod;
  requiresRendering = true;
}

void Application::onSelectionChange(long value) {
  const int delta = value > 0 ? +1 : -1;
  const int a = (state.selection + 3 + delta) % 3;
  state.selection = static_cast<Selection>(a);
  requiresRendering = true;
}

void Application::onWaveChange(long value) {
  const int delta = value > 0 ? +1 : -1;
  const int a = (state.wave + 3 + delta) % 3;
  state.wave = static_cast<Wave>(a);
  requiresRendering = true;
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

void Application::handle(InputEvent event) {
  onClick(event.click);
  onRotation(event.rotation);

  if (requiresRendering) {
    screen->render(state);
    requiresRendering = false;
  }
}