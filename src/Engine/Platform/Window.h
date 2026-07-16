#pragma once

#include <SDL3/SDL.h>
#include <string>

namespace Engine {

struct WindowDescription {
  std::string title = "Rockets";
  int width = 1280;
  int height = 720;
  bool resizable = true;
};

class Window {
public:
  Window() = default;
  ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  Window(Window &&other) noexcept;
  Window &operator=(Window &&other) noexcept;

  bool create(const WindowDescription &desc);

  void destroy();

  void show();
  void hide();

  void resize(int width, int height);

  void setTitle(const std::string &title);

  void minimize();
  void maximize();
  void restore();

  bool setFullscreen(bool enabled);
  void setBorderless(bool enabled);

  void focus();

  bool isFullscreen() const;
  bool isBorderless() const;
  bool isMinimized() const;
  bool isMaximized() const;

  void close();

  void onResized(int width, int height);

  SDL_Window *handle() const { return m_window; }

  int width() const { return m_width; }
  int height() const { return m_height; }

  float aspectRatio() const;

private:
  void moveFrom(Window &other) noexcept;

  SDL_Window *m_window = nullptr;

  int m_width = 0;
  int m_height = 0;

  SDL_WindowFlags m_flags = 0;
};

} // namespace Engine
