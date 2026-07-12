#pragma once

#include <SDL3/SDL_keycode.h>
#include <unordered_map>

namespace Engine {

class Keyboard {
public:
  Keyboard() = default;
  ~Keyboard() = default;

  void beginFrame();
  void endFrame();
  Keyboard(const Keyboard &) = delete;
  Keyboard &operator=(const Keyboard &) = delete;

  void keyDown(SDL_Keycode key);
  void keyUp(SDL_Keycode key);

  [[nodiscard]] bool pressed(SDL_Keycode key) const;
  [[nodiscard]] bool released(SDL_Keycode key) const;
  [[nodiscard]] bool justPressed(SDL_Keycode key) const;
  [[nodiscard]] bool justReleased(SDL_Keycode key) const;
  void clear();

private:
  std::unordered_map<SDL_Keycode, bool> m_current;
  std::unordered_map<SDL_Keycode, bool> m_previous;
};

} // namespace Engine
