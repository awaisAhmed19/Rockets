#pragma once
#include <SDL3/SDL_rect.h>
#include <cmath>
#include <iostream>

typedef float f32;
typedef int i32;

namespace math {

struct vector2D {
  f32 x = 0.f;
  f32 y = 0.f;

  vector2D(f32 _x, float _y) {
    x = _x;
    y = _y;
  }

  vector2D() {
    x = 0.f;
    y = 0.f;
  }
  f32 &operator[](int i) { return ((&x)[i]); }
  const f32 &operator[](int i) const { return ((&x)[i]); }

  vector2D &operator*=(f32 scalar) {
    x *= scalar;
    y *= scalar;
    return (*this);
  }

  vector2D &operator/=(f32 scalar) {
    scalar = 1.f / scalar;
    x /= scalar;
    y /= scalar;
    return (*this);
  }
  vector2D operator-(const vector2D &a) { return vector2D(x - a.x, y - a.y); }
  vector2D operator+(const vector2D &a) { return vector2D(x + a.x, y + a.y); }
  vector2D operator*(const vector2D &a) { return vector2D(x * a.x, y * a.y); }
  bool operator==(const vector2D &a) { return (x == a.x && y == a.y); }

  void invert() {
    x = -x;
    y = -y;
  }

  inline vector2D operator*(f32 scalar) {
    return (vector2D(x * scalar, y * scalar));
  }

  inline vector2D operator+(f32 scalar) {
    return (vector2D(x + scalar, y + scalar));
  }
  inline vector2D operator-(f32 scalar) {
    return (vector2D(x - scalar, y - scalar));
  }

  inline f32 scalarProduct(const vector2D &a) const {
    return (x * a.x) + (y * a.y);
  }

  inline f32 magnitude() const {
    return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
  }

  inline void normalize() {
    if (this->magnitude() < 0) {
      std::cerr << "division by zero in function this->normalize" << std::endl;
    }
    f32 mag = this->magnitude();
    this->x = this->x / mag;
    this->y = this->y / mag;
  }
  inline f32 crossProduct(vector2D &b) {
    return (this->x * b.y - this->y * b.x);
  }
  inline f32 dot(vector2D &b) { return (this->y * b.x) + (this->y * b.y); }
};

struct vector3 {
  f32 x = 0.f;
  f32 y = 0.f;
  f32 z = 0.f;
};

// 2d matrix
struct matrix2D {
  f32 a[2][2] = {{0.f, 0.f}, {0.f, 0.f}};

  matrix2D() = default;
  matrix2D(f32 _a00, f32 _a01, f32 _a10, f32 _a11) {
    a[0][0] = _a00;
    a[0][1] = _a01;
    a[1][0] = _a10;
    a[1][1] = _a11;
  }
  matrix2D(vector2D &_a, vector2D &_b) {
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

inline vector2D pow(const vector2D &a, const int power) {
  vector2D ret;
  ret.x = std::pow(a.x, power);
  ret.y = std::pow(a.y, power);
  return ret;
}

inline f32 vec_distance(vector2D &a, vector2D &b) {
  f32 x_2 = std::pow(a.x - b.x, 2);
  f32 y_2 = std::pow(a.y - b.y, 2);
  return std::sqrt(x_2 + y_2);
}
}; // namespace math

namespace physics {
// body has coords, mass, rect, bounding
struct rect {
  math::vector2D pos;
  i32 width = 0;
  i32 height = 0;

  rect(math::vector2D &pos, i32 _width, i32 _height) {
    this->pos = pos;
    this->width = _width;
    this->height = _height;
  }

  SDL_Rect getSDLRect() {
    return {(i32)this->pos.x, (i32)this->pos.y, this->width, this->height};
  }
};
struct body {
  f32 mass = 10.f;
  rect body;
};
}; // namespace physics
