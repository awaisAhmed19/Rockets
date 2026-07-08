#include "Application.h"
#include <iostream>
#include <map>
namespace App {

std::map<int, int> keys;
int frameSkip = 0;
int isRunning = 0;
int SCREENWIDTH = 1280;
int SCREENHEIGHT = 720;

// SDL_Window *window = nullptr;
Engine::Window window;
SDL_Renderer *renderer = nullptr;
SDL_Surface *surf = nullptr;

const std::string TITLE = "Rockets";

void draw() {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  // to draw;
  SDL_RenderPresent(renderer);
}

void fpsChange(int fps) {
  char szFps[128];
  sprintf(szFps, "%s: %d FPS", "Rocket Game - ", fps);
  SDL_SetWindowTitle(window.getWindowPointer(), szFps);
}

void onQuit() { isRunning = 0; }

void onKeyDown(SDL_Event *e) { keys[e->key.key] = 1; }

void onKeyUp(SDL_Event *e) { keys[e->key.key] = 0; }

void update() {
  if (keys[SDLK_LEFT]) {
    // move left
  } else if (keys[SDLK_RIGHT]) {
    // move right
  } else if (keys[SDLK_UP]) {
    // move UP
  } else if (keys[SDLK_DOWN]) {
    // move down
  }
}

void run() {

  int past = SDL_GetTicks();
  int now = past, pastFps = past;
  int fps = 0, frameSkipped = 0;

  SDL_Event event;

  while (isRunning) {
    int timeElapsed = 0;
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        onQuit();
        break;
      case SDL_EVENT_KEY_DOWN:
        onKeyDown(&event);
        break;
      case SDL_EVENT_KEY_UP:
        onKeyUp(&event);
        break;
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
      case SDL_EVENT_MOUSE_BUTTON_UP:
      case SDL_EVENT_MOUSE_MOTION:
        break;
      }
    }

    timeElapsed = (now = SDL_GetTicks()) - past;
    if (timeElapsed >= UPDATE_INTERVAL) {
      past = now;
      update();

      if (frameSkipped++ >= frameSkip) {
        draw();
      }
    }

    if (now - pastFps >= 1000) {
      pastFps = now;
      fpsChange(fps);
      fps = 0;
    }

    SDL_Delay(1);
  }
}
void start() {
  Engine::Window_description desc;

  desc.TITLE = TITLE;
  desc.width = SCREENWIDTH;
  desc.height = SCREENHEIGHT;
  desc.resizeable = true;

  if (!window.Init(desc)) {
    std::cerr << SDL_GetError() << '\n';
    SDL_Quit();
    return;
  }
  isRunning = 1;
  run();
}

void stop() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }
  window.shutdown();
  SDL_Quit();
}
}; // namespace App
