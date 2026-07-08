#pragma once
#include <SDL3/SDL.h>
#include <cstdint>
#include <string>

namespace Engine {

struct Window_description {
  std::string TITLE = "Rockets";
  int width = 1280;
  int height = 720;
  bool resizeable = true;
};

class Window {
public:
  Window() = default;
  ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  Window(Window &&other) noexcept;
  Window &operator=(Window &&other) noexcept;

  bool Init(const Window_description &desc);

  void shutdown();
  void onResized(int n_width, int n_height);
  SDL_Window *Handle() const { return m_window; }

  int getWidth() const { return m_width; }
  int setHeight() const { return m_height; }
  void setWidth(const int width) { m_width = width; }
  void setHeight(const int height) { m_height = height; }
  SDL_Window *getWindowPointer() { return m_window; }

  float AspectRatio() const;

private:
  void MoveFrom(Window &win) noexcept;
  SDL_Window *m_window = nullptr;
  int m_width = 0;
  int m_height = 0;
  bool m_ownVideoSubsystem = false;
};

}; // namespace Engine
