#pragma once

#include <SDL3/SDL_mouse.h>
#include <unordered_map>

namespace Engine {

class Mouse {
public:
  Mouse() = default;
  ~Mouse() = default;

  Mouse(const Mouse &) = delete;
  Mouse &operator=(const Mouse &) = delete;
  void beginFrame();
  void endFrame();
  void move(int x, int y);

  void buttonDown(Uint8 button);
  void buttonUp(Uint8 button);

  [[nodiscard]] bool pressed(Uint8 button) const;
  [[nodiscard]] bool released(Uint8 button) const;

  void wheel(float x, float y);

  [[nodiscard]] int x() const;
  [[nodiscard]] int y() const;

  [[nodiscard]] float scrollDeltaX() const;
  [[nodiscard]] float scrollDeltaY() const;

  [[nodiscard]] bool justPressed(Uint8 button) const;
  [[nodiscard]] bool justReleased(Uint8 button) const;
  void clear();

private:
  int m_x = 0;
  int m_y = 0;

  float m_scrollDeltaX = 0.0f;
  float m_scrollDeltaY = 0.0f;

  std::unordered_map<Uint8, bool> m_currentButtons;
  std::unordered_map<Uint8, bool> m_previousButtons;
};

} // namespace Engine
