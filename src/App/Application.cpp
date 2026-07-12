#include "Application.h"
#include "Engine/Core/Time.h"
#include <iostream>

const std::string TITLE = "Rockets";

void App::draw() {
  SDL_SetRenderDrawColor(m_renderer, 0, 114, 114, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(m_renderer);
  // to draw;
  SDL_RenderPresent(m_renderer);
}

void App::fpsChange(int fps) {
  m_window.setTitle(TITLE + " - " + std::to_string(fps) + " FPS");
}

void App::onQuit() { m_running = false; }

void App::onEvent(const Engine::Event &e) {
  switch (e.type) {
  case Engine::EventType::WindowClose:
    onQuit();
    break;

  case Engine::EventType::KeyDown:
    m_keyboard.keyDown(e.keyboard.key);
    break;

  case Engine::EventType::KeyUp:
    m_keyboard.keyUp(e.keyboard.key);
    break;

  case Engine::EventType::MouseMove:
    m_mouse.move(e.mouse.x, e.mouse.y);
    break;

  case Engine::EventType::MouseDown:
    m_mouse.buttonDown(e.mouse.button);
    break;

  case Engine::EventType::MouseUp:
    m_mouse.buttonUp(e.mouse.button);
    break;
  case Engine::EventType::MouseWheel:
    m_mouse.wheel(e.mouse.wheelX, e.mouse.wheelY);
    break;

  case Engine::EventType::WindowResize:
    m_window.onResized(e.window.width, e.window.height);
    break;
  default:
    break;
  }
}

void App::update(Engine::f64 deltaTime) {
  if (m_keyboard.pressed(SDLK_LEFT)) {
    // move left
  } else if (m_keyboard.pressed(SDLK_RIGHT)) {
    // move right
  } else if (m_keyboard.pressed(SDLK_UP)) {
    // move UP
  } else if (m_keyboard.pressed(SDLK_DOWN)) {
    // move down
  }
}

void App::run() {
  Engine::Timer frameTimer;
  Engine::Timer fpsTimer;

  Engine::Event event;

  int fps = 0;

  while (m_running) {
    m_keyboard.beginFrame();
    m_mouse.beginFrame();

    while (m_dispatcher.poll(event)) {
      onEvent(event);
    }

    if (frameTimer.milliseconds() >= UPDATE_INTERVAL) {
      Engine::f64 deltaTime = frameTimer.seconds();
      frameTimer.reset();

      update(deltaTime);
      draw();

      ++fps;
    }

    if (fpsTimer.seconds() >= 1.0) {
      fpsChange(fps);
      fps = 0;
      fpsTimer.reset();
    }

    m_keyboard.endFrame();
    m_mouse.endFrame();

    SDL_Delay(1);
  }
}

void App::start() {
  if (!m_platform.init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD)) {
    return;
  }

  Engine::WindowDescription desc;
  desc.title = TITLE;
  desc.width = SCREEN_WIDTH;
  desc.height = SCREEN_HEIGHT;

  if (!m_window.create(desc)) {
    stop();
    return;
  }
  m_renderer = SDL_CreateRenderer(m_window.handle(), nullptr);

  if (!m_renderer) {
    SDL_Log("%s", SDL_GetError());
    stop();
    return;
  }

  m_running = true;

  run();

  stop();
}

void App::stop() {
  if (m_renderer) {
    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
  }

  m_window.close();
  m_platform.shutdown();
}
