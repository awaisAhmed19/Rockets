#ifndef ROCKET_HPP
#define ROCKET_HPP
#include "globals.hpp"
#define ROCKET_W 30
#define ROCKET_H 60
#define MAX_V 100
#define MAX_TH 250

class Rocket {
   public:
    Rocket() {}
    float mass = 100.0f;
    float fuel = 100000.0f;
    float th_power = 200.0f;
    Vector2 pos = {0, 0};
    Vector2 vel = {0, 0};
    Vector2 acc = {0, 0};
    float angle = 2 * PI;
    float fc_rate = 20.0f;

    void update();
    bool hasFuel();
    void draw();
    bool landed();
    void applyGravity(float g);
    void thrust();
};
#endif  // !ROCKET_HPP
