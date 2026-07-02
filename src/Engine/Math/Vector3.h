#pragma once
#include "Engine/Math/Constants.h"
#include "Engine/core/core.h"
namespace Engine {
namespace math {
/*
[ ] magnitudeSquared()
[ ] normalized()
[ ] lerp()
[ ] clamp()
[ ] min()
[ ] max()
[ ] abs()
[ ] floor()
[ ] ceil()
[ ] round()
[ ] isZero()
[ ] isNormalized()
[ ] distanceSquared()
[ ] hadamardProduct()
[ ] projectOnto()
[ ] rejectFrom()
[ ] perpendicular() (vector3)
[ ] rotate() (vector3)
[ ] rotateAround() (vector3)
[ ] tripleProduct() (Vector3)
//contact math
[ ] reflect()
[ ] refract()
*/
struct vector3 {
  f32 x = 0.f;
  f32 y = 0.f;
  f32 z = 0.f;

  constexpr vector3() = default;
  constexpr vector3(f32 _x, f32 _y, f32 _z) : x(_x), y(_y), z(_z) {}
  f32 &operator[](int i) { return ((&x)[i]); }
  const f32 &operator[](int i) const { return ((&x)[i]); }
  inline vector3 operator*(const f32 scalar) const {
    return (vector3(x * scalar, y * scalar, z * scalar));
  }

  inline vector3 operator+(const f32 scalar) {
    return (vector3(x + scalar, y + scalar, z + scalar));
  }

  inline vector3 operator-(const f32 scalar) {
    return (vector3(x - scalar, y - scalar, z - scalar));
  }
  inline vector3 operator-(const vector3 &v) const {
    return vector3(x - v.x, y - v.y, z - v.z);
  }
  inline vector3 operator+(const vector3 &v) const {
    return vector3(x + v.x, y + v.y, z + v.z);
  }
  inline vector3 operator*(const vector3 &v) const {
    return vector3(x * v.x, y * v.y, z * v.z);
  }
  inline vector3 operator-() const { return vector3(-x, -y, -z); }

  inline vector3 operator/(const vector3 &v) const {
    RT_ASSERT(!v.isZero(),
              "Division by zero in math::vector3::this->operator/; Hint : "
              "check your input vector u/ v/ <- ");
    return vector3(x / v.x, y / v.y, z / v.z);
  }

  inline vector3 &operator*=(const f32 scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return (*this);
  }

  inline vector3 &operator/=(f32 scalar) {
    scalar = 1.f / scalar;
    RT_ASSERT(std::abs(scalar) > eps,
              "scalar less than or equal to zero in /= scalar");
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return (*this);
  }

  inline vector3 &operator-=(const vector3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  inline vector3 &operator+=(const vector3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  inline vector3 &operator*=(const vector3 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }
  inline vector3 &operator/=(const vector3 &v) {
    RT_ASSERT(!v.isZero(),
              "Division by zero in math::vector3::this->operator/; Hint : "
              "check your input vector u/ v <- ");
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
  }

  inline bool isZero() const {
    return (std::abs(x) < eps && std::abs(y) < eps && std::abs(z) < eps);
  }
  bool operator==(const vector3 &v) const {
    return (x == v.x && y == v.y && z == v.z);
  }

  bool operator!=(const vector3 &v) const {
    return (x != v.x && y != v.y && z != v.z);
  }

  inline friend vector3 operator*(f32 factor, const vector3 &u) {
    return vector3(factor * u.x, factor * u.y, factor * u.z);
  }

  inline friend vector3 operator-(f32 factor, const vector3 &u) {
    return vector3(factor - u.x, factor - u.y, factor - u.z);
  }

  inline friend vector3 operator+(f32 factor, const vector3 &u) {
    return vector3(factor + u.x, factor + u.y, factor + u.z);
  }

  inline friend vector3 operator/(f32 factor, const vector3 &u) {
    return vector3(factor / u.x, factor / u.y, factor / u.z);
  }

  void invert() {
    x = -x;
    y = -y;
    z = -z;
  }

  inline f32 scalarProduct(const vector3 &v) const {
    return (x * v.x) + (y * v.y) + (z * v.z);
  }

  inline f32 magnitude() const {
    f32 dx = x * x;
    f32 dy = y * y;
    f32 dz = z * z;
    return std::sqrt(dx + dy + dz);
  }
  inline f32 magnitudeSquared() const { return x * x + y * y + z * z; }

  inline void normalize() {
    f32 mag = this->magnitude();
    RT_ASSERT(!isZero(),
              "Division by zero in math::vector3::this->normalize; Hint : "
              "current vector has less than or zero magnitude ");
    *this /= mag;
  }

  inline vector3 normalized() const {
    f32 mag = this->magnitude();
    RT_ASSERT(mag > eps, "cannot normalize zero vector");
    return {x / mag, y / mag, z / mag};
  }

  inline vector3 crossProduct(const vector3 &v) const {
    return vector3((this->y * v.z - this->z * v.y),
                   (this->z * v.x - this->x * v.z),
                   (this->x * v.y - this->y * v.x));
  }
  inline f32 dot(const vector3 &v) const {
    return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
  }

  inline f32 angle(const vector3 &v) {
    f32 c = (this->dot(v)) / (this->magnitude() * v.magnitude());
    c = std::clamp(c, -1.f, 1.f);
    return std::acos(c);
  }
  inline bool isNormalized() const {
    return std::abs(this->magnitudeSquared() - 1.f) < eps;
  }
  inline f32 distance(const vector3 &v) const {
    f32 x_ = x - v.x;
    f32 y_ = y - v.y;
    f32 z_ = z - v.z;
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
  }
  inline f32 distanceSquared(const vector3 &v) const {
    f32 x_ = x - v.x;
    f32 y_ = y - v.y;
    f32 z_ = z - v.z;
    return (x_ * x_ + y_ * y_ + z_ * z_);
  }
  inline f32 scalarProjection(vector3 &v) const {
    return this->dot(v) / v.magnitude();
  }
  inline vector3 vectorProjection(vector3 &v) const {
    return v * (this->dot(v) / (v.magnitude() * v.magnitude()));
  }
  inline vector3 rejectFrom(vector3 &v) const {
    return *this - this->vectorProjection(v);
  }
  // rotate around a point
  vector3 rotateAround(const vector3 &point, const vector3 &axis,
                       float radians) const;
  vector3 reflect(const vector3 &normal) const {
    RT_ASSERT(normal.isNormalized(),
              "Reflection requires a normalized normal.");

    return *this - normal * (2.f * dot(normal));
  }
  bool nearEqual(const vector3 &v) const {
    return std::abs(x - v.x) < eps && std::abs(y - v.y) < eps &&
           std::abs(z - v.z) < eps;
  }
  inline f32 maxComponent() const { return std::max({x, y, z}); }
  inline f32 minComponent() const { return std::min({x, y, z}); }
  vector3 hadamardProduct(const vector3 &v) const {
    return {x * v.x, y * v.y, z * v.z};
  }
  vector3 clampMagnitude(float maxLength) const {
    float len = magnitude();
    if (len <= maxLength)
      return *this;
    return normalized() * maxLength;
  }
  inline vector3 rotateX(f32 radians) const {
    f32 c = std::cos(radians);
    f32 s = std::sin(radians);
    return {x, y * c - z * s, y * s + z * c};
  }
  inline vector3 rotateY(f32 radians) const {
    f32 c = std::cos(radians);
    f32 s = std::sin(radians);
    return {x * c + z * s, y, -x * s + z * c};
  }
  inline vector3 rotateZ(f32 radians) const {
    f32 c = std::cos(radians);
    f32 s = std::sin(radians);
    return {x * c - y * s, (x * s) + (y * c), z};
  }

  vector3 refract(const vector3 &normal, float eta) const {
    float cosi = std::clamp(dot(normal), -1.f, 1.f);
    float k = 1.f - eta * eta * (1.f - cosi * cosi);

    if (k < 0)
      return {};
    return (*this) * eta - normal * (eta * cosi + std::sqrt(k));
  }
  vector3 lerp(const vector3 &v, float t) const {
    return *this + (v - *this) * t;
  }
  vector3 tripleProduct(const vector3 &b, const vector3 &c) const {
    return crossProduct(b.crossProduct(c));
  }
};

inline vector3 max(const vector3 &u, const vector3 &v) {
  return vector3(std::max(u.x, v.x), std::max(u.y, v.y), std::max(u.z, v.z));
}
inline vector3 min(const vector3 &u, const vector3 &v) {
  return vector3(std::min(u.x, v.x), std::min(u.y, v.y), std::min(u.z, v.z));
}
inline vector3 maxlength(const vector3 &u, const vector3 &v) {
  return u.magnitudeSquared() > v.magnitudeSquared() ? u : v;
}
inline vector3 minlength(const vector3 &u, const vector3 &v) {
  return u.magnitudeSquared() < v.magnitudeSquared() ? u : v;
}

inline vector3 abs(const vector3 &u) {
  return vector3(std::abs(u.x), std::abs(u.y), std::abs(u.z));
}

inline vector3 ceil(const vector3 &u) {
  return vector3(std::ceil(u.x), std::ceil(u.y), std::ceil(u.z));
}
inline vector3 floor(const vector3 &u) {
  return vector3(std::floor(u.x), std::floor(u.y), std::floor(u.z));
}
inline vector3 round(const vector3 &u) {
  return vector3(std::round(u.x), std::round(u.y), std::round(u.z));
}
}; // namespace math

}; // namespace Engine
