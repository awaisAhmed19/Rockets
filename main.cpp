#include "raylib.h"

int main() {
    InitWindow(400, 400, "Rockets");

    Vector2 rocketPos = {200, 200};
    Vector2 rocketVel = {0, 0};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_SPACE)) rocketVel.y -= 0.5f;
        rocketVel.y += 0.1f;
        rocketPos.y += rocketVel.y;
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("press Space to launch", 10, 10, 20, RAYWHITE);
        DrawRectangle(rocketPos.x, rocketPos.y, 20, 60, RED);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
