
#pragma once
#include "Engine/Math/Constants.h"
#include "Engine/Math/Vector2.h"
#include "Engine/Math/Vector3.h"
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
[ ] perpendicular() (vector4)
[ ] rotate() (vector4)
[ ] rotateAround() (vector4)
[ ] tripleProduct() (vector4)
//contact math
[ ] reflect()
[ ] refract()
*/
struct vector4 {
  f32 x = 0.f;
  f32 y = 0.f;
  f32 z = 0.f;
  f32 w = 0.f;

  constexpr vector4() = default;
  constexpr vector4(f32 _x, f32 _y, f32 _z, f32 _w)
      : x(_x), y(_y), z(_z), w(_w) {}
  f32 &operator[](int i) { return ((&x)[i]); }
  const f32 &operator[](int i) const { return ((&x)[i]); }
  inline vector4 operator*(const f32 scalar) const {
    return (vector4(x * scalar, y * scalar, z * scalar, w * scalar));
  }

  inline vector4 operator+(const f32 scalar) {
    return (vector4(x + scalar, y + scalar, z + scalar, w + scalar));
  }

  inline vector4 operator-(const f32 scalar) {
    return (vector4(x - scalar, y - scalar, z - scalar, w - scalar));
  }
  inline vector4 operator-(const vector4 &v) const {
    return vector4(x - v.x, y - v.y, z - v.z, w - v.w);
  }
  inline vector4 operator+(const vector4 &v) const {
    return vector4(x + v.x, y + v.y, z + v.z, w + v.w);
  }
  inline vector4 operator*(const vector4 &v) const {
    return vector4(x * v.x, y * v.y, z * v.z, w * v.w);
  }
  inline vector4 operator-() const { return vector4(-x, -y, -z, -w); }

  inline vector4 operator/(const vector4 &v) const {
    RT_ASSERT(!v.isZero(),
              "Division by zero in math::vector4::this->operator/; Hint : "
              "check your input vector u/ v/ <- ");
    return vector4(x / v.x, y / v.y, z / v.z, w / v.w);
  }

  inline vector4 &operator*=(const f32 scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return (*this);
  }

  inline vector4 &operator/=(f32 scalar) {
    scalar = 1.f / scalar;
    RT_ASSERT(std::abs(scalar) > eps,
              "scalar less than or equal to zero in /= scalar");
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return (*this);
  }

  inline vector4 &operator-=(const vector4 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }
  inline vector4 &operator+=(const vector4 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }
  inline vector4 &operator*=(const vector4 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
  }
  inline vector4 &operator/=(const vector4 &v) {
    RT_ASSERT(!v.isZero(),
              "Division by zero in math::vector4::this->operator/; Hint : "
              "check your input vector u/ v <- ");
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
  }

  inline bool isZero() const {
    return (std::abs(x) < eps && std::abs(y) < eps && std::abs(z) < eps &&
            std::abs(w) < eps);
  }
  bool operator==(const vector4 &v) const {
    return (x == v.x && y == v.y && z == v.z && w == v.w);
  }

  bool operator!=(const vector4 &v) const {
    return (x != v.x && y != v.y && z != v.z && w != v.w);
  }

  inline friend vector4 operator*(f32 factor, const vector4 &u) {
    return vector4(factor * u.x, factor * u.y, factor * u.z, factor * u.w);
  }

  inline friend vector4 operator-(f32 factor, const vector4 &u) {
    return vector4(factor - u.x, factor - u.y, factor - u.z, factor - u.w);
  }

  inline friend vector4 operator+(f32 factor, const vector4 &u) {
    return vector4(factor + u.x, factor + u.y, factor + u.z, factor + u.w);
  }

  inline friend vector4 operator/(f32 factor, const vector4 &u) {
    return vector4(factor / u.x, factor / u.y, factor / u.z, factor / u.z);
  }

  void invert() {
    x = -x;
    y = -y;
    z = -z;
    w = -w;
  }

  inline f32 scalarProduct(const vector4 &v) const {
    return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
  }

  inline f32 magnitude() const {
    f32 dx = x * x;
    f32 dy = y * y;
    f32 dz = z * z;
    f32 dw = w * w;
    return std::sqrt(dx + dy + dz + dw);
  }
  inline f32 magnitudeSquared() const { return x * x + y * y + z * z + w * w; }

  inline void normalize() {
    f32 mag = this->magnitude();
    RT_ASSERT(!isZero(),
              "Division by zero in math::vector4::this->normalize; Hint : "
              "current vector has less than or zero magnitude ");
    *this /= mag;
  }

  inline vector4 normalized() const {
    f32 mag = this->magnitude();
    RT_ASSERT(mag > eps, "cannot normalize zero vector");
    return {x / mag, y / mag, z / mag, w / mag};
  }

  // inline vector4 crossProduct(const vector4 &v) const {
  //   return vector4((this->y * v.z - this->z * v.y),
  //                  (this->z * v.x - this->x * v.z),
  //                  (this->x * v.y - this->y * v.x));
  // }
  inline f32 dot(const vector4 &v) const {
    return (this->x * v.x) + (this->y * v.y) + (this->z * v.z) +
           (this->w * v.w);
  }

  inline f32 angle(const vector4 &v) {
    f32 c = (this->dot(v)) / (this->magnitude() * v.magnitude());
    c = std::clamp(c, -1.f, 1.f);
    return std::acos(c);
  }
  inline bool isNormalized() const {
    return std::abs(this->magnitudeSquared() - 1.f) < eps;
  }
  inline f32 distance(const vector4 &v) const {
    f32 x_ = x - v.x;
    f32 y_ = y - v.y;
    f32 z_ = z - v.z;
    f32 w_ = w - v.w;
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
  }
  inline f32 distanceSquared(const vector4 &v) const {
    f32 x_ = x - v.x;
    f32 y_ = y - v.y;
    f32 z_ = z - v.z;
    f32 w_ = w - v.w;
    return (x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
  }
  inline f32 scalarProjection(vector4 &v) const {
    return this->dot(v) / v.magnitude();
  }
  inline vector4 vectorProjection(vector4 &v) const {
    return v * (this->dot(v) / (v.magnitude() * v.magnitude()));
  }
  inline vector4 rejectFrom(vector4 &v) const {
    return *this - this->vectorProjection(v);
  }
  // rotate around a point
  vector4 rotateAround(const vector4 &point, const vector4 &axis,
                       float radians) const;
  vector4 reflect(const vector4 &normal) const {
    RT_ASSERT(normal.isNormalized(),
              "Reflection requires a normalized normal.");

    return *this - normal * (2.f * dot(normal));
  }
  bool nearEqual(const vector4 &v) const {
    return std::abs(x - v.x) < eps && std::abs(y - v.y) < eps &&
           std::abs(z - v.z) < eps && std::abs(w - v.w) < eps;
  }
  inline f32 maxComponent() const { return std::max({x, y, z, w}); }
  inline f32 minComponent() const { return std::min({x, y, z, w}); }
  vector4 hadamardProduct(const vector4 &v) const {
    return {x * v.x, y * v.y, z * v.z, w * v.w};
  }
  vector4 clampMagnitude(float maxLength) const {
    float len = magnitude();
    if (len <= maxLength)
      return *this;
    return normalized() * maxLength;
  }

  vector4 refract(const vector4 &normal, float eta) const {
    float cosi = std::clamp(dot(normal), -1.f, 1.f);
    float k = 1.f - eta * eta * (1.f - cosi * cosi);

    if (k < 0)
      return {};
    return (*this) * eta - normal * (eta * cosi + std::sqrt(k));
  }
  vector4 lerp(const vector4 &v, float t) const {
    return *this + (v - *this) * t;
  }

  vector3 xyz() const {
    f32 nx = x;
    f32 ny = y;
    f32 nz = z;
    return vector3(nx, ny, nz);
  }
  vector2 xy() const {
    f32 nx = x;
    f32 ny = y;
    return vector2(nx, ny);
  }
};

inline vector4 max(const vector4 &u, const vector4 &v) {
  return vector4(std::max(u.x, v.x), std::max(u.y, v.y), std::max(u.z, v.z),
                 std::max(u.w, v.w));
}
inline vector4 min(const vector4 &u, const vector4 &v) {
  return vector4(std::min(u.x, v.x), std::min(u.y, v.y), std::min(u.z, v.z),
                 std::min(u.w, v.w));
}
inline vector4 maxlength(const vector4 &u, const vector4 &v) {
  return u.magnitudeSquared() > v.magnitudeSquared() ? u : v;
}
inline vector4 minlength(const vector4 &u, const vector4 &v) {
  return u.magnitudeSquared() < v.magnitudeSquared() ? u : v;
}

inline vector4 abs(const vector4 &u) {
  return vector4(std::abs(u.x), std::abs(u.y), std::abs(u.z), std::abs(u.w));
}

inline vector4 ceil(const vector4 &u) {
  return vector4(std::ceil(u.x), std::ceil(u.y), std::ceil(u.z),
                 std::ceil(u.w));
}
inline vector4 floor(const vector4 &u) {
  return vector4(std::floor(u.x), std::floor(u.y), std::floor(u.z),
                 std::floor(u.w));
}
inline vector4 round(const vector4 &u) {
  return vector4(std::round(u.x), std::round(u.y), std::round(u.z),
                 std::round(u.z));
}
}; // namespace math

}; // namespace Engine
