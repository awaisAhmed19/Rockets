#include "globals.hpp"
#define ROCKET_W 30
#define ROCKET_H 60

struct Rocket {
    // float mass=100;
    // float thrust=100;
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    void update();
    void draw();
    void applyGravity(float g);
    void thrust();
};
