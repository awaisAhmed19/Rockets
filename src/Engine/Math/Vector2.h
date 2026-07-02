#pragma once
#include "Engine/Math/Constants.h"
#include "Engine/core/core.h"
#include <cmath>
namespace Engine {

namespace math {
/*
[X] magnitudeSquared()
[X] normalized()
[X] lerp()
[X] clamp()
[X] min()
[X] max()
[X] abs()
[X] floor()
[X] ceil()
[X] round()
[X] isZero()
[X] isNormalized()
[X] distanceSquared()
[X] hadamardProduct()
[X] projectOnto()
[X] rejectFrom()
[X] perpendicular() (Vector2)
[X] rotate() (Vector2)
[X] rotateAround() (Vector2)
[ ] tripleProduct() (Vector3)
//contact math
[ ] reflect()
[ ] refract()
*/
struct vector2 {
  f32 x = 0.f;
  f32 y = 0.f;

  constexpr vector2() = default;
  constexpr vector2(f32 x, f32 y) : x(x), y(y) {}

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
  inline friend vector2 operator*(f32 factor, const vector2 &u) {
    return vector2(factor * u.x, factor * u.y);
  }

  inline friend vector2 operator-(f32 factor, const vector2 &u) {
    return vector2(factor - u.x, factor - u.y);
  }

  inline friend vector2 operator+(f32 factor, const vector2 &u) {
    return vector2(factor + u.x, factor + u.y);
  }

  inline friend vector2 operator/(f32 factor, const vector2 &u) {
    return vector2(factor / u.x, factor / u.y);
  }

  inline vector2 &operator-=(const vector2 &v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  inline vector2 &operator+=(const vector2 &v) {
    x += v.x;
    y += v.y;
    return *this;
  }
  inline vector2 &operator*=(const vector2 &v) {
    x *= v.x;
    y *= v.y;
    return *this;
  }
  inline vector2 operator/=(const vector2 &v) {
    RT_ASSERT(!v.isZero(),
              "Division by zero in math::vector2::this->operator/; Hint : "
              "check your input vector u/ v <- ");
    x /= v.x;
    y /= v.y;
    return *this;
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
    RT_ASSERT(std::abs(scalar) > eps, "Division by zero");
    scalar = 1.f / scalar;
    x *= scalar;
    y *= scalar;
    return (*this);
  }

  inline bool isZero() const {
    return (std::abs(x) < eps && std::abs(y) < eps);
  }

  inline vector2 lerp(const vector2 &v, f32 t) {
    return vector2(x + ((v.x - x) * t), y + ((v.y - y) * t));
  }
  inline f32 magnitude() const {
    return std::sqrt((this->x * this->x) + (this->y * this->y));
  }
  inline f32 magnitudeSquared() const { return x * x + y * y; }

  inline float length() const { return magnitude(); }
  inline vector2 magnitudeClamp(const f32 max_length) const {
    if (this->length() > max_length) {
      return (*this / this->length()) * max_length;
    }
    return *this;
  }

  inline vector2 cclamp(const f32 min_x, const f32 min_y, const f32 max_x,
                        const f32 max_y) const {
    return vector2(std::clamp(x, min_x, max_x), std::clamp(y, min_y, max_y));
  }

  inline vector2 normalized() const {
    float mag = this->magnitude();
    RT_ASSERT(mag > eps, "cannot normalize zero vector");
    return {x / mag, y / mag};
  }

  inline void normalize() {
    f32 mag = this->magnitude();
    RT_ASSERT(mag > eps, "Cannot normalize zero vector");
    this->x /= mag;
    this->y /= mag;
  }
  inline f32 crossProduct(const vector2 &v) const {
    return (this->x * v.y - this->y * v.x);
  }
  inline f32 dot(const vector2 &v) const {
    return (this->x * v.x) + (this->y * v.y);
  }
  inline f32 angle(const vector2 &v) const {
    f32 c = ((this->dot(v)) / (this->magnitude() * v.magnitude()));
    c = std::clamp(c, -1.f, 1.f);
    return std::acos(c);
  }

  inline bool isNormalized() const {
    return std::abs(this->magnitudeSquared() - 1.f) < eps;
  }

  inline f32 distance(vector2 &v) const {
    f32 dx = x - v.x;
    f32 dy = y - v.y;
    return std::sqrt(dx * dx + dy * dy);
  }

  inline f32 distanceSquared(vector2 &v) const {
    f32 dx = x - v.x;
    f32 dy = y - v.y;
    return dx * dx + dy * dy;
  }

  inline f32 scalarProjection(vector2 &v) const {
    return (this->dot(v)) / v.magnitude();
  }
  inline vector2 hadamardProduct(const vector2 &v) const {
    return {x * v.x, y * v.y};
  }
  inline vector2 vectorProjection(vector2 &v) const {
    return v * (this->dot(v) / (v.magnitude() * v.magnitude()));
  }
  inline vector2 rejectFrom(vector2 &v) const {
    return *this - this->vectorProjection(v);
  }
  // rotate around a point
  vector2 rotateAround(const vector2 &center, float angle) const {
    return (*this - center).rotate(angle) + center;
  }
  vector2 reflect(const vector2 &normal) const {
    return *this - normal * (2.f * dot(normal));
  }
  bool nearEqual(const vector2 &v) const {
    return std::abs(x - v.x) < eps && std::abs(y - v.y) < eps;
  }
  float maxComponent() const { return std::max(x, y); }
  float minComponent() const { return std::min(x, y); }
  inline vector2 perpendicular() const { return vector2(-y, x); }
  inline vector2 perpendicularCW() const { return vector2(y, -x); }
  inline vector2 rotate(const i32 angle) const {
    float r = angle * Pi / 180.f;
    return vector2(x * std::cos(r) - y * std::sin(r),
                   x * std::sin(r) + y * std::cos(r));
  }
};

inline vector2 max(const vector2 &u, const vector2 &v) {
  return vector2(std::max(u.x, v.x), std::max(u.y, v.y));
}
inline vector2 min(const vector2 &u, const vector2 &v) {
  return vector2(std::min(u.x, v.x), std::min(u.y, v.y));
}
inline vector2 maxlength(const vector2 &u, const vector2 &v) {
  return u.magnitudeSquared() > v.magnitudeSquared() ? u : v;
}
inline vector2 minlength(const vector2 &u, const vector2 &v) {
  return u.magnitudeSquared() < v.magnitudeSquared() ? u : v;
}

inline vector2 abs(const vector2 &u) {
  return vector2(std::abs(u.x), std::abs(u.y));
}

inline vector2 ceil(const vector2 &u) {
  return vector2(std::ceil(u.x), std::ceil(u.y));
}
inline vector2 floor(const vector2 &u) {
  return vector2(std::floor(u.x), std::floor(u.y));
}
inline vector2 round(const vector2 &u) {
  return vector2(std::round(u.x), std::round(u.y));
}
}; // namespace math
}; // namespace Engine
