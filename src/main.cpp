#include "Engine/Platform/Window.h"
#include "Engine/core/Tester.h"
// #include "core/core.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <cassert>
#include <iostream>
#include <map>

#include "Engine/core/Config/ConfigFile.h"
#include "Engine/core/Config/Entry.h"
#include "Engine/core/Config/PrimitiveEntry.h"
#include "Engine/core/Config/StringEntry.h"
#include "Engine/core/Config/VectorEntry.h"
#define UPDATE_INTERVAL 1000 / 60

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 640;

std::map<int, int> keys;
int frameSkip = 0;
int isRunning = 0;

SDL_Window *window = nullptr;
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
  SDL_SetWindowTitle(window, szFps);
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
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    return;
  }

  if (!SDL_CreateWindowAndRenderer(TITLE.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT,
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    std::cerr << "Window did not create! SDL err:" << SDL_GetError()
              << std::endl;
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

  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }

  SDL_Quit();
}

using namespace Engine::Config;

static void print_config(const GenHashMap &map) {
  std::cout << "---------------------------------\n";

  for (const auto &[name, entry] : map) {
    std::string type;
    std::string value;

    type = entry->type_name();
    entry->write_val_string(&value);

    std::cout << type << " " << name << " = " << value << '\n';
  }
  std::cout << "---------------------------------\n";
}
int main() {
  GenHashMap config;
  config["int"] = new IntEntry(42);
  config["title"] = new StringEntry("Hello Engine");
  config["position"] = new VectorFloatEntry({1.0f, 2.0f, 3.0f});

  std::cout << "\nInitial values\n";

  print_config(config);

  bool ok = SaveFile("config.cfg", config, "Config parser test");

  assert(ok);

  static_cast<IntEntry *>(config["int"])->set(-100);

  static_cast<StringEntry *>(config["title"])->set("Changed");

  static_cast<VectorFloatEntry *>(config["position"])->set({9.f, 9.f, 9.f});

  std::cout << "\nModified values\n";

  print_config(config);

  ok = LoadFile("config.cfg", config);

  assert(ok);

  std::cout << "\nReloaded values\n";

  print_config(config);

  int value = static_cast<IntEntry *>(config["int"])->get();

  assert(value == 42);

  std::string text = static_cast<StringEntry *>(config["title"])->get();

  assert(text == "Hello Engine");

  std::vector<float> vec =
      static_cast<VectorFloatEntry *>(config["position"])->get();

  assert(vec.size() == 3);
  assert(vec[0] == 1.f);
  assert(vec[1] == 2.f);
  assert(vec[2] == 3.f);

  clear_genhashmap(config);

  std::cout << "\nAll ConfigFile tests passed!\n";

  return 0;
}
