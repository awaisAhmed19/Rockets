#pragma once

#include "EventType.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_mouse.h>

namespace Engine {

struct KeyboardEvent {
  SDL_Keycode key = 0;
  bool repeat = false;
};

struct MouseEvent {
  int x = 0;
  int y = 0;

  Uint8 button = 0;

  float wheelX = 0;
  float wheelY = 0;
};

struct WindowEvent {
  int width = 0;
  int height = 0;
};

class Event {
public:
  Event() : type(EventType::None), handled(false) {}
  ~Event() = default;

  EventType type = EventType::None;
  bool handled = false;

  Event(const Event &) = default;
  Event &operator=(const Event &) = default;

  static bool translate(const SDL_Event &sdlEvent, Event &event);

  union {
    MouseEvent mouse;
    KeyboardEvent keyboard;
    WindowEvent window;
  };
};

} // namespace Engine
