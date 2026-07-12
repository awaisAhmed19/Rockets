#pragma once
#include "Engine/Event/Event.h"
namespace Engine {
class EventDispatcher {
public:
  bool poll(Event &event);

private:
  SDL_Event m_sdlEvent;
};
}; // namespace Engine
