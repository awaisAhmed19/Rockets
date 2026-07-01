#pragma once
#include "Engine/core/core.h"
namespace Engine {
namespace math {

struct vector3 {
  f32 x = 0.f;
  f32 y = 0.f;
  f32 z = 0.f;

  vector3(f32 _x, f32 _y, f32 _z) {
    x = _x;
    y = _y;
    z = _z;
  }

  vector3() {
    x = 0.f;
    y = 0.f;
    z = 0.f;
  }
  f32 &operator[](int i) { return ((&x)[i]); }
  const f32 &operator[](int i) const { return ((&x)[i]); }

  vector3 &operator*=(const f32 scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return (*this);
  }

  vector3 &operator/=(f32 scalar) {
    scalar = 1.f / scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return (*this);
  }
  vector3 operator-(const vector3 &v) {
    return vector3(x - v.x, y - v.y, z - v.z);
  }
  vector3 operator+(const vector3 &v) {
    return vector3(x + v.x, y + v.y, z + v.z);
  }
  vector3 operator*(const vector3 &v) {
    return vector3(x * v.x, y * v.y, z * v.z);
  }
  vector3 operator-() { return vector3(-x, -y, -z); }

  vector3 operator/(const vector3 &v) {
    RT_ASSERT(v.x == 0 && v.y == 0 && v.z == 0,
              "Division by zero in math::vector3::this->operator/; Hint : "
              "check your input vector u/ v/ <- ");
    return vector3(x / v.x, y / v.y, z / v.z);
  }

  bool operator==(const vector3 &v) {
    return (x == v.x && y == v.y && z == v.z);
  }

  bool operator!=(const vector3 &v) {
    return (x != v.x && y != v.y && z != v.z);
  }
  void invert() {
    x = -x;
    y = -y;
    z = -z;
  }

  inline vector3 operator*(const f32 scalar) {
    return (vector3(x * scalar, y * scalar, z * scalar));
  }

  inline vector3 operator+(const f32 scalar) {
    return (vector3(x + scalar, y + scalar, z + scalar));
  }
  inline vector3 operator-(const f32 scalar) {
    return (vector3(x - scalar, y - scalar, z - scalar));
  }

  inline f32 scalarProduct(const vector3 &v) const {
    return (x * v.x) + (y * v.y) + (z * v.z);
  }

  inline f32 magnitude() const {
    return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) +
                     std::pow(this->z, 2));
  }

  inline void normalize() {

    RT_ASSERT((this->magnitude() == 0),
              "Division by zero in math::vector3::this->normalize; Hint : "
              "current vector has less than or zero magnitude ");
    f32 mag = this->magnitude();
    *this /= mag;
  }
  inline vector3 crossProduct(const vector3 &v) {
    return vector3((this->y * v.z - this->z * v.y),
                   (this->z * v.x - this->x * v.z),
                   (this->x * v.y - this->y * v.x));
  }
  inline f32 dot(const vector3 &v) {
    return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
  }

  inline f32 angle(const vector3 &v) {
    return std::acos(((this->dot(v)) / (this->magnitude() * v.magnitude())));
  }
};

inline f32 vec_distance(const vector3 &u, const vector3 &v) {
  f32 x_2 = std::pow(u.x - v.x, 2);
  f32 y_2 = std::pow(u.y - v.y, 2);
  f32 z_2 = std::pow(u.z - v.z, 2);
  return std::sqrt(x_2 + y_2 + z_2);
}

inline f32 scalarProjection(vector3 &u, vector3 &v) {
  return (u.dot(v)) / (v.magnitude() * v.magnitude());
}
inline vector3 vectorProjection(vector3 &u, vector3 &v) {
  return v * scalarProjection(u, v);
}
}; // namespace math

}; // namespace Engine
