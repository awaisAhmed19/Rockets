
#pragma once
#include "Engine/Core/Config/VectorEntry.h"
#include "Engine/Core/Core.h"
#include "Engine/Event/Event.h"
#include "Engine/Event/EventDispatcher.h"
#include "Engine/Input/Keyboard.h"
#include "Engine/Input/Mouse.h"
#include "Engine/Platform/Platform.h"
#include "Engine/Platform/Window.h"
#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <cassert>
#define UPDATE_INTERVAL 1000 / 60

class App {

private:
  Engine::Platform m_platform;
  Engine::Window m_window;
  Engine::Window m_window2;
  static constexpr int SCREEN_WIDTH = 1280;
  static constexpr int SCREEN_HEIGHT = 720;
  SDL_Renderer *m_renderer = nullptr;
  bool m_running = false;
  int m_frameSkip = 0;

  Engine::Keyboard m_keyboard;
  Engine::Mouse m_mouse;
  Engine::EventDispatcher m_dispatcher;

public:
  void draw();

  void fpsChange(int fps);

  void onQuit();

  void onEvent(const Engine::Event &e);
  void update(Engine::f64 deltaTime);
  void update();
  void init();
  void run();
  void start();
  void stop();
};
