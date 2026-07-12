#include "Event.h"

namespace Engine {

bool Event::translate(const SDL_Event &sdlEvent, Event &event) {
  event.handled = false;

  switch (sdlEvent.type) {
  case SDL_EVENT_KEY_DOWN:
    event.type = EventType::KeyDown;
    event.keyboard.key = sdlEvent.key.key;
    event.keyboard.repeat = sdlEvent.key.repeat;
    return true;

  case SDL_EVENT_KEY_UP:
    event.type = EventType::KeyUp;
    event.keyboard.key = sdlEvent.key.key;
    event.keyboard.repeat = false;
    return true;

  case SDL_EVENT_MOUSE_MOTION:
    event.type = EventType::MouseMove;
    event.mouse.x = sdlEvent.motion.x;
    event.mouse.y = sdlEvent.motion.y;
    return true;

  case SDL_EVENT_MOUSE_BUTTON_DOWN:
    event.type = EventType::MouseDown;
    event.mouse.button = sdlEvent.button.button;
    event.mouse.x = sdlEvent.button.x;
    event.mouse.y = sdlEvent.button.y;
    return true;

  case SDL_EVENT_MOUSE_BUTTON_UP:
    event.type = EventType::MouseUp;
    event.mouse.button = sdlEvent.button.button;
    event.mouse.x = sdlEvent.button.x;
    event.mouse.y = sdlEvent.button.y;
    return true;

  case SDL_EVENT_MOUSE_WHEEL:
    event.type = EventType::MouseWheel;
    event.mouse.wheelX = sdlEvent.wheel.x;
    event.mouse.wheelY = sdlEvent.wheel.y;
    return true;

  case SDL_EVENT_WINDOW_RESIZED:
    event.type = EventType::WindowResize;
    event.window.width = sdlEvent.window.data1;
    event.window.height = sdlEvent.window.data2;
    return true;

  case SDL_EVENT_WINDOW_FOCUS_GAINED:
    event.type = EventType::WindowFocus;
    return true;

  case SDL_EVENT_WINDOW_FOCUS_LOST:
    event.type = EventType::WindowLostFocus;
    return true;

  case SDL_EVENT_QUIT:
    event.type = EventType::WindowClose;
    return true;

  default:
    event.type = EventType::None;
    return false;
  }
}

} // namespace Engine
