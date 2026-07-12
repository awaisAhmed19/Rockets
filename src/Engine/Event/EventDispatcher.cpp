#include "EventDispatcher.h"
namespace Engine {

bool EventDispatcher::poll(Event &event) {
  while (SDL_PollEvent(&m_sdlEvent)) {
    if (Event::translate(m_sdlEvent, event))
      return true;
  }

  return false;
}
} // namespace Engine
