#include "Keyboard.h"

namespace Engine {

void Keyboard::keyDown(SDL_Keycode key) { m_current[key] = true; }
void Keyboard::keyUp(SDL_Keycode key) { m_current[key] = false; }
bool Keyboard::pressed(SDL_Keycode key) const {
  auto it = m_current.find(key);
  return it != m_current.end() && it->second;
}

bool Keyboard::released(SDL_Keycode key) const { return !pressed(key); }
bool Keyboard::justPressed(SDL_Keycode key) const {
  const bool current = m_current.count(key) ? m_current.at(key) : false;
  const bool previous = m_previous.count(key) ? m_previous.at(key) : false;
  return current && !previous;
}
bool Keyboard::justReleased(SDL_Keycode key) const {
  const bool current = m_current.count(key) ? m_current.at(key) : false;
  const bool previous = m_previous.count(key) ? m_previous.at(key) : false;
  return !current && previous;
}
void Keyboard::clear() { m_current.clear(); }
void Keyboard::beginFrame() {
  // Nothing to do yet
}

void Keyboard::endFrame() { m_previous = m_current; }
} // namespace Engine
