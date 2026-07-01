#pragma once
#include "Engine/Math/Constants.h"
#include "Engine/core/core.h"
namespace Engine {

namespace math {
/*
[X] magnitudeSquared()
[X] normalized()
[ ] lerp()
[ ] clamp()
[ ] min()
[ ] max()
[ ] abs()
[ ] floor()
[ ] ceil()
[ ] round()
[X] isZero()
[X] isNormalized()
[X] distanceSquared()
[ ] hadamardProduct()
[X] projectOnto()
[ ] rejectFrom()
[ ] perpendicular() (Vector2)
[ ] rotate() (Vector2)
[ ] rotateAround() (Vector2)
[ ] tripleProduct() (Vector3)
//contact math
[ ] reflect()
[ ] refract()
*/
struct vector2;
vector2 vectorProjection(vector2 &u, vector2 v);
vector2 scalarProjection(vector2 &u, vector2 v);
struct vector2 {
  f32 x = 0.f;
  f32 y = 0.f;

  vector2(f32 _x, f32 _y) {
    x = _x;
    y = _y;
  }

  vector2() {
    x = 0.f;
    y = 0.f;
  }
  f32 &operator[](int i) { return ((&x)[i]); }
  const f32 &operator[](int i) const { return ((&x)[i]); }

  inline vector2 operator-(const vector2 &v) const {
    return vector2(x - v.x, y - v.y);
  }
  inline vector2 operator-() const { return vector2(-x, -y); }
  vector2 operator+(const vector2 &v) const {
    return vector2(x + v.x, y + v.y);
  }
  inline vector2 operator*(const vector2 &v) const {
    return vector2(x * v.x, y * v.y);
  }

  inline vector2 operator/(const vector2 &v) const {
    RT_ASSERT(!v.isZero(),
              "Division by zero in math::vector2::this->operator/; Hint : "
              "check your input vector u/ v <- ");
    return vector2(x / v.x, y / v.y);
  }

  inline vector2 operator-=(const vector2 &v) {
    return vector2(x -= v.x, y -= v.y);
  }
  inline vector2 operator+=(const vector2 &v) {
    return vector2(x += v.x, y += v.y);
  }
  inline vector2 operator*=(const vector2 &v) {
    return vector2(x *= v.x, y *= v.y);
  }

  inline vector2 operator/=(const vector2 &v) {
    RT_ASSERT(!v.isZero(),
              "Division by zero in math::vector2::this->operator/; Hint : "
              "check your input vector u/ v <- ");
    return vector2(x /= v.x, y /= v.y);
  }
  inline bool operator==(const vector2 &v) const {
    return (x == v.x && y == v.y);
  }
  inline bool operator!=(const vector2 &v) const {
    return (x != v.x && y != v.y);
  }
  inline void invert() {
    x = -x;
    y = -y;
  }

  inline vector2 operator*(const f32 scalar) const {
    return (vector2(x * scalar, y * scalar));
  }

  inline vector2 operator/(const f32 scalar) const {
    RT_ASSERT(
        scalar != 0,
        "Division by zero in math::vector2::this->operator/scalar; Hint : "
        "check your input scalar <- ");

    return (vector2(x / scalar, y / scalar));
  }
  inline vector2 operator+(const f32 scalar) const {
    return (vector2(x + scalar, y + scalar));
  }
  inline vector2 operator-(const f32 scalar) const {
    return (vector2(x - scalar, y - scalar));
  }

  inline vector2 &operator*=(f32 scalar) {
    x *= scalar;
    y *= scalar;
    return (*this);
  }
  inline vector2 &operator+=(f32 scalar) {
    x += scalar;
    y += scalar;
    return (*this);
  }
  inline vector2 &operator-=(f32 scalar) {
    x -= scalar;
    y -= scalar;
    return (*this);
  }
  inline vector2 &operator/=(f32 scalar) {
    scalar = 1.f / scalar;
    x *= scalar;
    y *= scalar;
    return (*this);
  }

  inline bool isZero() const {
    return (std::abs(x) < eps && std::abs(y) < eps);
  }

  inline f32 magnitude() const {
    return std::sqrt((this->x * this->x) + (this->y * this->y));
  }

  inline f32 magnitude_sq() const { return magnitude() * magnitude(); }
  inline vector2 normalized() const {
    return vector2(x / magnitude(), y / magnitude());
  }

  inline void normalize() {
    RT_ASSERT((this->magnitude() < 0 || this->magnitude() == 0),
              "Division by zero in math::vector2::this->normalize; Hint : "
              "current vector has less than or zero magnitude ");
    f32 mag = this->magnitude();
    this->x /= mag;
    this->y /= mag;
  }
  inline f32 crossProduct(const vector2 &v) {
    return (this->x * v.y - this->y * v.x);
  }
  inline f32 dot(const vector2 &v) { return (this->x * v.x) + (this->y * v.y); }
  inline f32 angle(const vector2 &v) {
    return std::acos(((this->dot(v)) / (this->magnitude() * v.magnitude())));
  }

  inline bool isNormalized() {
    return std::abs(this->magnitude_sq() - 1.f) < eps;
  }

  inline f32 distance(vector2 &v) {
    f32 x_2 = x * x - v.x * v.x;
    f32 y_2 = y * y - v.y * v.y;
    return std::sqrt(x_2 + y_2);
  }

  inline f32 distance_sq(vector2 &v) {
    return this->distance(v) * this->distance(v);
  }

  inline float scalarProjection(vector2 &v) {
    return (this->dot(v)) / (v.magnitude() * v.magnitude());
  }

  inline vector2 vectorProjection(vector2 &v) {
    return v * this->scalarProjection(v);
  }
  inline vector2 rejectFrom(vector2 &v) {
    return *this - this->vectorProjection(v);
  }
};

}; // namespace math
}; // namespace Engine
