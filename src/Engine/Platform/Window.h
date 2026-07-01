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

  void Shutdown();
  void OnResized(int n_width, int n_height);
  SDL_Window *Handle() const { return m_window; }

  int Width() const { return m_width; }
  int Height() const { return m_height; }

  float AspectRatio() const;

private:
  void MoveFrom(Window &win) noexcept;
  SDL_Window *m_window = nullptr;
  int m_width = 0;
  int m_height = 0;
  bool m_ownVideoSubsystem = false;
};

}; // namespace Engine
