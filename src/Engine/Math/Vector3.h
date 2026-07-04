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
[ ] perpendicular() (Vector3)
[ ] rotate() (Vector3)
[ ] rotateAround() (Vector3)
[ ] tripleProduct() (Vector3)
//contact math
[ ] reflect()
[ ] refract()
*/
struct Vector3 {
  f32 x = 0.f;
  f32 y = 0.f;
  f32 z = 0.f;

  constexpr Vector3() = default;
  constexpr Vector3(f32 _x, f32 _y, f32 _z) : x(_x), y(_y), z(_z) {}
  constexpr Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z) {}
  f32 &operator[](int i) { return ((&x)[i]); }
  const f32 &operator[](int i) const { return ((&x)[i]); }
  inline Vector3 operator*(const f32 scalar) const {
    return (Vector3(x * scalar, y * scalar, z * scalar));
  }

  inline Vector3 operator+(const f32 scalar) {
    return (Vector3(x + scalar, y + scalar, z + scalar));
  }

  inline Vector3 operator-(const f32 scalar) {
    return (Vector3(x - scalar, y - scalar, z - scalar));
  }
  inline Vector3 operator-(const Vector3 &v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
  }
  inline Vector3 operator+(const Vector3 &v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
  }
  inline Vector3 operator*(const Vector3 &v) const {
    return Vector3(x * v.x, y * v.y, z * v.z);
  }
  inline Vector3 operator-() const { return Vector3(-x, -y, -z); }

  inline Vector3 operator/(const Vector3 &v) const {
    RT_ASSERT(!v.isZero(),
              "Division by zero in math::Vector3::this->operator/; Hint : "
              "check your input vector u/ v/ <- ");
    return Vector3(x / v.x, y / v.y, z / v.z);
  }

  inline Vector3 &operator*=(const f32 scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return (*this);
  }

  inline Vector3 &operator/=(f32 scalar) {
    scalar = 1.f / scalar;
    RT_ASSERT(std::abs(scalar) > eps,
              "scalar less than or equal to zero in /= scalar");
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return (*this);
  }

  inline Vector3 &operator-=(const Vector3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  inline Vector3 &operator+=(const Vector3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  inline Vector3 &operator*=(const Vector3 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }
  inline Vector3 &operator/=(const Vector3 &v) {
    RT_ASSERT(!v.isZero(),
              "Division by zero in math::Vector3::this->operator/; Hint : "
              "check your input vector u/ v <- ");
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
  }

  inline bool isZero() const {
    return (std::abs(x) < eps && std::abs(y) < eps && std::abs(z) < eps);
  }
  bool operator==(const Vector3 &v) const {
    return (x == v.x && y == v.y && z == v.z);
  }

  bool operator!=(const Vector3 &v) const {
    return (x != v.x || y != v.y || z != v.z);
  }

  inline friend Vector3 operator*(f32 factor, const Vector3 &u) {
    return Vector3(factor * u.x, factor * u.y, factor * u.z);
  }

  inline friend Vector3 operator-(f32 factor, const Vector3 &u) {
    return Vector3(factor - u.x, factor - u.y, factor - u.z);
  }

  inline friend Vector3 operator+(f32 factor, const Vector3 &u) {
    return Vector3(factor + u.x, factor + u.y, factor + u.z);
  }

  inline friend Vector3 operator/(f32 factor, const Vector3 &u) {
    return Vector3(factor / u.x, factor / u.y, factor / u.z);
  }

  void invert() {
    x = -x;
    y = -y;
    z = -z;
  }

  inline f32 scalarProduct(const Vector3 &v) const {
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
              "Division by zero in math::Vector3::this->normalize; Hint : "
              "current vector has less than or zero magnitude ");
    *this /= mag;
  }

  inline Vector3 normalized() const {
    f32 mag = this->magnitude();
    RT_ASSERT(mag > eps, "cannot normalize zero vector");
    return {x / mag, y / mag, z / mag};
  }

  inline Vector3 crossProduct(const Vector3 &v) const {
    return Vector3((this->y * v.z - this->z * v.y),
                   (this->z * v.x - this->x * v.z),
                   (this->x * v.y - this->y * v.x));
  }
  inline f32 dot(const Vector3 &v) const {
    return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
  }

  inline f32 angle(const Vector3 &v) const {
    f32 c = (this->dot(v)) / (this->magnitude() * v.magnitude());
    c = std::clamp(c, -1.f, 1.f);
    return std::acos(c);
  }
  inline bool isNormalized() const {
    return std::abs(this->magnitudeSquared() - 1.f) < eps;
  }
  inline f32 distance(const Vector3 &v) const {
    f32 x_ = x - v.x;
    f32 y_ = y - v.y;
    f32 z_ = z - v.z;
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
  }
  inline f32 distanceSquared(const Vector3 &v) const {
    f32 x_ = x - v.x;
    f32 y_ = y - v.y;
    f32 z_ = z - v.z;
    return (x_ * x_ + y_ * y_ + z_ * z_);
  }
  inline f32 scalarProjection(const Vector3 &v) const {
    return this->dot(v) / v.magnitude();
  }
  inline Vector3 vectorProjection(const Vector3 &v) const {
    return v * (this->dot(v) / (v.magnitude() * v.magnitude()));
  }
  inline Vector3 rejectFrom(const Vector3 &v) const {
    return *this - this->vectorProjection(v);
  }
  // rotate around a point
  Vector3 rotateAround(const Vector3 &point, const Vector3 &axis,
                       float radians) const;
  Vector3 reflect(const Vector3 &normal) const {
    RT_ASSERT(normal.isNormalized(),
              "Reflection requires a normalized normal.");

    return *this - normal * (2.f * dot(normal));
  }
  bool nearEqual(const Vector3 &v) const {
    return std::abs(x - v.x) < eps && std::abs(y - v.y) < eps &&
           std::abs(z - v.z) < eps;
  }
  inline f32 maxComponent() const { return std::max({x, y, z}); }
  inline f32 minComponent() const { return std::min({x, y, z}); }
  Vector3 hadamardProduct(const Vector3 &v) const {
    return {x * v.x, y * v.y, z * v.z};
  }
  Vector3 clampMagnitude(const float maxLength) const {
    float len = magnitude();
    if (len <= maxLength)
      return *this;
    return normalized() * maxLength;
  }
  inline Vector3 rotateX(const f32 radians) const {
    f32 c = std::cos(radians);
    f32 s = std::sin(radians);
    return {x, y * c - z * s, y * s + z * c};
  }
  inline Vector3 rotateY(const f32 radians) const {
    f32 c = std::cos(radians);
    f32 s = std::sin(radians);
    return {x * c + z * s, y, -x * s + z * c};
  }
  inline Vector3 rotateZ(const f32 radians) const {
    f32 c = std::cos(radians);
    f32 s = std::sin(radians);
    return {x * c - y * s, (x * s) + (y * c), z};
  }

  Vector3 refract(const Vector3 &normal, float eta) const {
    float cosi = std::clamp(dot(normal), -1.f, 1.f);
    float k = 1.f - eta * eta * (1.f - cosi * cosi);

    if (k < 0)
      return {};
    return (*this) * eta - normal * (eta * cosi + std::sqrt(k));
  }
  Vector3 lerp(const Vector3 &v, float t) const {
    return *this + (v - *this) * t;
  }
  inline Vector3 slerp(const Vector3 &v, f32 t) const {
    f32 theta = std::acos(std::clamp(dot(v), -1.f, 1.f));
    if (theta < 0.001)
      return lerp(v, t);
    f32 sintheta = std::sin(theta);
    f32 ratioA = std::sin((1 - t) * theta) / sintheta;
    f32 ratioB = std::sin(t * theta) / sintheta;

    return {x * ratioA + v.x * ratioB, y * ratioA + v.y * ratioB,
            z * ratioA + v.z * ratioB};
  }
  Vector3 tripleProduct(const Vector3 &b, const Vector3 &c) const {
    return crossProduct(b.crossProduct(c));
  }
};

inline Vector3 max(const Vector3 &u, const Vector3 &v) {
  return Vector3(std::max(u.x, v.x), std::max(u.y, v.y), std::max(u.z, v.z));
}
inline Vector3 min(const Vector3 &u, const Vector3 &v) {
  return Vector3(std::min(u.x, v.x), std::min(u.y, v.y), std::min(u.z, v.z));
}
inline Vector3 maxlength(const Vector3 &u, const Vector3 &v) {
  return u.magnitudeSquared() > v.magnitudeSquared() ? u : v;
}
inline Vector3 minlength(const Vector3 &u, const Vector3 &v) {
  return u.magnitudeSquared() < v.magnitudeSquared() ? u : v;
}

inline Vector3 abs(const Vector3 &u) {
  return Vector3(std::abs(u.x), std::abs(u.y), std::abs(u.z));
}

inline Vector3 ceil(const Vector3 &u) {
  return Vector3(std::ceil(u.x), std::ceil(u.y), std::ceil(u.z));
}
inline Vector3 floor(const Vector3 &u) {
  return Vector3(std::floor(u.x), std::floor(u.y), std::floor(u.z));
}
inline Vector3 round(const Vector3 &u) {
  return Vector3(std::round(u.x), std::round(u.y), std::round(u.z));
}
}; // namespace math

}; // namespace Engine
