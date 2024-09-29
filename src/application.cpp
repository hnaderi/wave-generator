#include "application.hpp"
#include "data.hpp"

void Application::onFreqChange(long delta) {
  if (delta == 0)
    return;

  state.freq += delta;
  requiresRendering = true;
}

void Application::onModChange(Mod mod) {
  state.mod = mod;
  requiresRendering = true;
}

void Application::onClick(Click type) {
  if (type == Click::None)
    return;
  if (state.mod == Mod::Off)
    onModChange(Mod::On);
  else if (state.mod == Mod::On)
    onModChange(Mod::Off);
}

void Application::handle(InputEvent event) {
  onClick(event.click);
  if (state.mod == Mod::On)
    onFreqChange(event.rotation);

  if (requiresRendering) {
    screen->render(state);
    requiresRendering = false;
  }
}
