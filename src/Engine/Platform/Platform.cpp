#include "Platform.h"
#include "Engine/Core/Logger.h"

namespace Engine {

Platform::~Platform() { shutdown(); }

bool Platform::init(SDL_InitFlags flags) {
  if (m_initialized)
    return true;

  m_flags = flags;

  if (!SDL_Init(flags)) {
    Logger::err("SDL_Init failed");
    return false;
  }

  m_initialized = true;
  return true;
}

void Platform::shutdown() {
  if (!m_initialized)
    return;

  SDL_Quit();

  m_initialized = false;
  m_flags = 0;
}

} // namespace Engine
