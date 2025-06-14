#ifndef PLANET_HPP
#define PLANET_HPP

#include <string>

#include "globals.hpp"

class Planet {
   private:
    const float ground_w = 2000.0f;
    const float ground_h = 40.0f;

    std::string name;
    Color color;
    float radius;
    float atmosphere;
    Vector2 pos;
    float gravity;

   public:
    // Constructor
    Planet(std::string name, Vector2 pos, float radius, float gravity, Color color,
           float atmosphere = 0.0f);

    // Getters
    float getGround_h() const;
    float getGround_w() const;
    float getGravity() const;
    Vector2 getPos() const;
    std::string getName() const;

    // Drawing method
    void draw();
};

#endif  // PLANET_HPP
