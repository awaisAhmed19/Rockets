#include "Mouse.h"

namespace Engine {

void Mouse::move(int x, int y) {
  m_x = x;
  m_y = y;
}

void Mouse::buttonDown(Uint8 button) { m_currentButtons[button] = true; }
void Mouse::buttonUp(Uint8 button) { m_currentButtons[button] = false; }

bool Mouse::justPressed(Uint8 button) const {
  const bool current =
      m_currentButtons.count(button) ? m_currentButtons.at(button) : false;
  const bool previous =
      m_previousButtons.count(button) ? m_previousButtons.at(button) : false;
  return current && !previous;
}
bool Mouse::justReleased(Uint8 button) const {
  const bool current =
      m_currentButtons.count(button) ? m_currentButtons.at(button) : false;
  const bool previous =
      m_previousButtons.count(button) ? m_previousButtons.at(button) : false;
  return !current && previous;
}

void Mouse::endFrame() { m_previousButtons = m_currentButtons; }
bool Mouse::pressed(Uint8 button) const {
  auto it = m_currentButtons.find(button);
  return it != m_currentButtons.end() && it->second;
}

bool Mouse::released(Uint8 button) const { return !pressed(button); }
void Mouse::wheel(float x, float y) {
  m_scrollDeltaX = x;
  m_scrollDeltaY = y;
}

int Mouse::x() const { return m_x; }
int Mouse::y() const { return m_y; }

float Mouse::scrollDeltaX() const { return m_scrollDeltaX; }
float Mouse::scrollDeltaY() const { return m_scrollDeltaY; }
void Mouse::beginFrame() {
  m_scrollDeltaX = 0.0f;
  m_scrollDeltaY = 0.0f;
}

void Mouse::clear() {
  m_currentButtons.clear();

  m_x = 0;
  m_y = 0;

  m_scrollDeltaX = 0.0f;
  m_scrollDeltaY = 0.0f;
}

} // namespace Engine
