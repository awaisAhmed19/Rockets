#include <math.h>

#include "globals.hpp"

Camera2D cam = {0};
Rocket R;

cam.target = (Vector2){R.pos.x + 20.0f, R.pos.y + 20.0f};
cam.offset = (Vector2){SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f};

cam.zoom = 1.0f;

void Zoom() {
    cam.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove() * 0.1f));
    if (cam.zoom > 3.0f)
        cam.zoom = 3.0f;
    else if (cam.zoom < 0.1f)
        cam.zoom = 0.1f;
}
