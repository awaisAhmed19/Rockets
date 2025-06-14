#ifndef GAMECAMERA_HPP
#define GAMECAMERA_HPP
#include "globals.hpp"
#include "rocket.hpp"

class GameCamera {
   public:
    Camera2D cam;
    GameCamera(const Rocket R);
    void Zoom();
    void update(const Rocket R);
};
#endif  // !GAMECAMERA_HPP
