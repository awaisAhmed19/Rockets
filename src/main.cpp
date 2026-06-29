#include "core/core.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <iostream>
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 640;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Surface *surf = nullptr;

const std::string TITLE = "Rockets";

void CreateWindow() {
  window = SDL_CreateWindow(TITLE.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_RESIZABLE);
  if (!window) {
    std::cerr << "Window did not create! SDL err:" << SDL_GetError()
              << std::endl;
    SDL_Quit();
    return;
  }

  renderer = SDL_CreateRenderer(window, NULL);
  if (renderer == nullptr) {
    std::cerr << "renderer did not create! SDL err:" << SDL_GetError()
              << std::endl;
    SDL_Quit();
    return;
  }
}

int main() {
  std::cout << "Hello world";
  bool isRunning = true;
  SDL_Event e;
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    return -1;
  }
  CreateWindow();
  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_EVENT_QUIT) {
        isRunning = false;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }
  SDL_DestroySurface(surf);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
