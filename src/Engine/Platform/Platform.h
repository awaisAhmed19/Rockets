#pragma once

#include <SDL3/SDL.h>

namespace Engine {

class Platform {
public:
  Platform() = default;
  ~Platform();

  Platform(const Platform &) = delete;
  Platform &operator=(const Platform &) = delete;

  bool init(SDL_InitFlags flags);
  void shutdown();

  bool initialized() const { return m_initialized; }

private:
  SDL_InitFlags m_flags = 0;
  bool m_initialized = false;
};

} // namespace Engine
