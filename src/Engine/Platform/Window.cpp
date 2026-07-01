#include "Window.h"

namespace Engine {

Window::~Window() { Shutdown(); }

Window::Window(Window &&other) noexcept { MoveFrom(other); }

Window &Window::operator=(Window &&other) noexcept {
  if (this != &other) {
    Shutdown();
    MoveFrom(other);
  }
  return *this;
}

void Window::MoveFrom(Window &other) noexcept {
  m_window = other.m_window;
  m_width = other.m_width;
  m_height = other.m_height;
  m_ownVideoSubsystem = other.m_ownVideoSubsystem;

  other.m_window = nullptr;
  other.m_height = 0;
  other.m_width = 0;
  other.m_ownVideoSubsystem = false;
}

bool Window::Init(const Window_description &desc) {
  if (m_window != nullptr) {
    SDL_Log("Engine :: Window::Init called on an already initialized Window");
    return false;
  }

  const int width = desc.width > 0 ? desc.width : 1;
  const int height = desc.height > 0 ? desc.height : 1;

  const bool videoAlreadyInit = SDL_WasInit(SDL_INIT_VIDEO) != 0;
  if (SDL_InitSubSystem(SDL_INIT_VIDEO)) {
    SDL_Log("Failed to initialize SDL Video Subsystem: %s", SDL_GetError());
    return false;
  }

  m_ownVideoSubsystem = !videoAlreadyInit;

  SDL_WindowFlags flags = 0;

  if (desc.resizeable) {
    flags |= SDL_WINDOW_RESIZABLE;
  }

  m_window = SDL_CreateWindow(desc.TITLE.c_str(), width, height, flags);

  if (m_window == nullptr) {
    SDL_Log("Failed to Create a Widnow: %s", SDL_GetError());
    if (m_ownVideoSubsystem) {
      SDL_QuitSubSystem(SDL_INIT_VIDEO);
      m_ownVideoSubsystem = false;
    }
    return false;
  }
  m_width = width;
  m_height = height;
  return true;
}

void Window::Shutdown() {

  if (m_window != nullptr) {
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
  }
  if (m_ownVideoSubsystem) {
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    m_ownVideoSubsystem = false;
  }

  m_width = 0;
  m_height = 0;
}

void Window::OnResized(int n_width, int n_height) {
  if (n_width > 0) {
    m_width = n_width;
  }
  if (n_height > 0) {
    m_height = n_height;
  }
}

float Window::AspectRatio() const {
  return m_height > 0
             ? static_cast<float>(m_width) / static_cast<float>(m_height)
             : 0.0f;
}
}; // namespace Engine
