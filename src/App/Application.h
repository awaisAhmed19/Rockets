
#include "Engine/Core/Tester.h"
#include "Engine/Platform/Window.h"
// #include "core/core.h"
#include "Engine/Core/Config/VectorEntry.h"
#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <cassert>
#define UPDATE_INTERVAL 1000 / 60
namespace App {

void draw();

void fpsChange(int fps);

void onQuit();

void onKeyDown(SDL_Event *e);

void onKeyUp(SDL_Event *e);
void update();
void init();
void run();
void start();
void stop();
}; // namespace App
