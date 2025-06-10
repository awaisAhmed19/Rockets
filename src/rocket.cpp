#include "rocket.hpp"

#include <iostream>

#include "globals.hpp"

void Rocket::update() {
    pos.y += vel.y * DELTA_T;
    applyGravity(GRAVITY);
    if (pos.y > SCREENHEIGHT - ROCKET_H) {
        pos.y = SCREENHEIGHT - ROCKET_H;
        if (vel.y > 0) vel.y = 0;
    }
}

void Rocket::applyGravity(float g) { vel.y += g; }

void Rocket::thrust() {
    vel.y -= 8.0f;
    std::cout << "🚀 Thrust!\n" << vel.y;
}

void Rocket::draw() { DrawRectangle(pos.x, pos.y, ROCKET_W, ROCKET_H, RED); }
