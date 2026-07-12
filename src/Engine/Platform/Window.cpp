#include "Window.h"
#include <SDL3/SDL_video.h>

namespace Engine {

Window::~Window() { close(); }

Window::Window(Window &&other) noexcept { moveFrom(other); }

Window &Window::operator=(Window &&other) noexcept {
  if (this != &other) {
    close();
    moveFrom(other);
  }
  return *this;
}

void Window::moveFrom(Window &other) noexcept {
  m_window = other.m_window;
  m_width = other.m_width;
  m_height = other.m_height;

  other.m_window = nullptr;
  other.m_height = 0;
  other.m_width = 0;
}
void Window::minimize() { SDL_MinimizeWindow(m_window); }
void Window::maximize() { SDL_MaximizeWindow(m_window); }
bool Window::init(const WindowDescription &desc) {
  if (m_window)
    return false;

  m_flags = 0;

  return true;
}
void Window::close() {
  if (m_window) {
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
  }

  m_width = 0;
  m_height = 0;
}

void Window::onResized(int n_width, int n_height) {
  if (n_width > 0) {
    m_width = n_width;
  }
  if (n_height > 0) {
    m_height = n_height;
  }
}
void Window::restore() { SDL_RestoreWindow(m_window); }
void Window::focus() { SDL_RaiseWindow(m_window); }
bool Window::setFullscreen(bool enabled) {
  return SDL_SetWindowFullscreen(m_window, enabled);
}
void Window::setBorderless(bool enabled) {
  SDL_SetWindowBordered(m_window, !enabled);
}
float Window::aspectRatio() const {
  return m_height > 0
             ? static_cast<float>(m_width) / static_cast<float>(m_height)
             : 0.0f;
}
bool Window::isFullscreen() const {
  return (SDL_GetWindowFlags(m_window) & SDL_WINDOW_FULLSCREEN) != 0;
}

bool Window::isBorderless() const {
  return (SDL_GetWindowFlags(m_window) & SDL_WINDOW_BORDERLESS) != 0;
}

bool Window::isMinimized() const {
  return (SDL_GetWindowFlags(m_window) & SDL_WINDOW_MINIMIZED) != 0;
}

bool Window::isMaximized() const {
  return (SDL_GetWindowFlags(m_window) & SDL_WINDOW_MAXIMIZED) != 0;
}
bool Window::create(const WindowDescription &desc) {
  if (!init(desc))
    return false;

  m_window =
      SDL_CreateWindow(desc.title.c_str(), desc.width, desc.height, m_flags);

  if (!m_window) {
    SDL_Log("Failed: %s", SDL_GetError());
    return false;
  }

  m_width = desc.width;
  m_height = desc.height;
  return true;
}
void Window::show() { SDL_ShowWindow(m_window); }
void Window::hide() { SDL_HideWindow(m_window); }
void Window::resize(int w, int h) { SDL_SetWindowSize(m_window, w, h); }
void Window::setTitle(const std::string &title) {
  SDL_SetWindowTitle(m_window, title.c_str());
}
}; // namespace Engine
