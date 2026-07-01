#pragma once
#include "Engine/Math/Vector2.h"
#include "Engine/core/core.h"
// 2d matrix
//
namespace Engine {
namespace math {

struct matrix2D {
  f32 a[2][2] = {{0.f, 0.f}, {0.f, 0.f}};

  matrix2D() = default;
  matrix2D(f32 _a00, f32 _a01, f32 _a10, f32 _a11) {
    a[0][0] = _a00;
    a[0][1] = _a01;
    a[1][0] = _a10;
    a[1][1] = _a11;
  }
  matrix2D(vector2 &_a, vector2 &_b) {
    a[0][0] = _a.x;
    a[0][1] = _a.y;
    a[1][0] = _b.x;
    a[1][1] = _b.y;
  }

  matrix2D operator+(const matrix2D &_a) {
    return matrix2D(a[0][0] + _a.a[0][0], a[0][1] + _a.a[0][1],
                    a[1][0] + _a.a[1][0], a[1][1] + _a.a[1][1]);
  }
  matrix2D operator-(const matrix2D &_a) {
    return matrix2D(a[0][0] - _a.a[0][0], a[0][1] - _a.a[0][1],
                    a[1][0] - _a.a[1][0], a[1][1] - _a.a[1][1]);
  }
  matrix2D operator*(const matrix2D &_a) {
    matrix2D ret;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        ret.a[i][j] += this->a[i][j] * _a.a[i][j];
      }
      return ret;
    }
    return matrix2D(a[0][0] * _a.a[0][0], a[0][1] * _a.a[0][1],
                    a[1][0] * _a.a[1][0], a[1][1] * _a.a[1][1]);
  }

  matrix2D operator+(const f32 s) {
    return matrix2D(a[0][0] + s, a[0][1] + s, a[1][0] + s, a[1][1] + s);
  }
  matrix2D operator-(const f32 s) {
    return matrix2D(a[0][0] - s, a[0][1] - s, a[1][0] - s, a[1][1] + s);
  }
  matrix2D operator*(const f32 s) {
    return matrix2D(a[0][0] * s, a[0][1] * s, a[1][0] * s, a[1][1] + s);
  }
};
}; // namespace math

}; // namespace Engine
