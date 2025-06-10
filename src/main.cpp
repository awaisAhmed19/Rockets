#include "globals.hpp"
#include "raylib.h"
#include "rocket.hpp"
int main() {
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Rockets");
    SetTargetFPS(60);
    Rocket R;
    R.vel = {0.0f, 0.0f};
    R.pos = {SCREENWIDTH / 2.0f, SCREENHEIGHT};
    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_SPACE)) {
            R.thrust();
        }
        R.update();
        BeginDrawing();
        ClearBackground(BLACK);
        R.draw();
        // DrawLine(0, SCREENHEIGHT - ROCKET_H, SCREENWIDTH, SCREENHEIGHT - ROCKET_H, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
