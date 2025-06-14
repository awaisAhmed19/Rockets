#include "GameCamera.hpp"

GameCamera::GameCamera(const Rocket R) {
    cam.target = (Vector2){R.pos.x, R.pos.y - 20.0f};
    cam.offset = (Vector2){SCREENWIDTH / 2.0f, SCREENHEIGHT - ROCKET_H};
    cam.zoom = 1.0f;
    cam.rotation = 0.0f;
}

float Lerp(float a, float b, float t) { return a + t * (b - a); }
void GameCamera::update(const Rocket R) {
    cam.target = R.pos;
    //
    // cam.target.x = Lerp(cam.target.x, R.pos.x, 0.1f);
    // cam.target.y = Lerp(cam.target.y, R.pos.y, 0.1f);
}
void GameCamera::Zoom() {
    cam.zoom = expf(logf(cam.zoom) + ((float)GetMouseWheelMove() * 0.1f));

    if (cam.zoom > 3.0f)
        cam.zoom = 3.0f;
    else if (cam.zoom < 0.1f)
        cam.zoom = 0.1f;
}
