#include "GameCamera.hpp"
#include "globals.hpp"
#include "rocket.hpp"
int main() {
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Rockets");
    SetTargetFPS(60);
    Rocket R;
    GameCamera cam(R);
    R.vel = {0.0f, 0.0f};
    R.pos = {SCREENWIDTH / 2.0f, SCREENHEIGHT};
    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_SPACE)) {
            R.thrust();
        }
        cam.update(R);
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(cam.cam);
        R.update();
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
