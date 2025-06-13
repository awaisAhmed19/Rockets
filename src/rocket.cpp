#include "rocket.hpp"

#include <iostream>

#include "globals.hpp"
const float epsilon = 0.1f;
void Rocket::update() {
    acc = {0, 0};
    if (pos.y < SCREENHEIGHT - ROCKET_H) applyGravity(GRAVITY);

    vel.y += acc.y * DELTA_T;
    pos.y += vel.y * DELTA_T;

    if (pos.y > SCREENHEIGHT - ROCKET_H) {
        pos.y = SCREENHEIGHT - ROCKET_H;
        if (vel.y > epsilon) vel.y = 0;
    }
    draw();
}
bool Rocket::hasFuel() { return fuel > 0; }
bool Rocket::landed() { return vel.y < 25 && pos.y == SCREENHEIGHT - ROCKET_H; }
void Rocket::applyGravity(float g) { acc.y += g; }

void Rocket::thrust() {
    if (!hasFuel()) {
        return;
    }
    acc.y -= th_power;
    fuel -= fc_rate * DELTA_T;

    if (fuel < 0) fuel = 0;
    std::cout << "🚀 Thrust! Fuel left: " << fuel << "\n";
}

void Rocket::draw() { DrawRectangle(pos.x, pos.y, ROCKET_W, ROCKET_H, RED); }
