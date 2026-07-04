#pragma once
#include "Engine/Math/Constants.h"
#include "Engine/Math/Vector2.h"
#include "Engine/Math/Vector3.h"
#include "Engine/Math/Vector4.h"
#include "Engine/core/core.h"
namespace Engine {
namespace math {
struct quaternion {
  f32 w = 0.f;
  f32 x = 0.f;
  f32 y = 0.f;
  f32 z = 0.f;
  constexpr quaternion() = default;
  constexpr quaternion(f32 _w, f32 _x, f32 _y, f32 _z)
      : w(_w), x(_x), y(_y), z(_z) {}
  constexpr quaternion(f32 _w, const Vector3 &v)
      : w(_w), x(v.x), y(v.y), z(v.z) {}
  quaternion(const Vector4 &v) {
    w = v.w;
    x = v.x;
    y = v.y;
    z = v.z;
  }
  f32 &operator[](int i) { return ((&x)[i]); }
  const f32 &operator[](int i) const { return ((&x)[i]); }
  inline quaternion operator*(const f32 scalar) const {
    return (quaternion(x * scalar, y * scalar, z * scalar, w * scalar));
  }

  inline quaternion operator+(const f32 scalar) {
    return (quaternion(x + scalar, y + scalar, z + scalar, w + scalar));
  }

  inline quaternion operator-(const f32 scalar) {
    return (quaternion(x - scalar, y - scalar, z - scalar, w - scalar));
  }
  inline quaternion operator-(const quaternion &v) const {
    return quaternion(x - v.x, y - v.y, z - v.z, w - v.w);
  }
  inline quaternion operator+(const quaternion &v) const {
    return quaternion(x + v.x, y + v.y, z + v.z, w + v.w);
  }
  inline quaternion operator*(const quaternion &v) const {
    return quaternion(x * v.x, y * v.y, z * v.z, w * v.w);
  }
  inline quaternion operator-() const { return quaternion(-x, -y, -z, -w); }

  inline quaternion operator/(const quaternion &v) const {
    RT_ASSERT(!v.isZero(),
              "Division by zero in math::quaternion::this->operator/; Hint : "
              "check your input vector u/ v/ <- ");
    return quaternion(x / v.x, y / v.y, z / v.z, w / v.w);
  }

  inline quaternion &operator*=(const f32 scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return (*this);
  }

  inline quaternion &operator/=(f32 scalar) {
    scalar = 1.f / scalar;
    RT_ASSERT(std::abs(scalar) > eps,
              "scalar less than or equal to zero in /= scalar");
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return (*this);
  }

  inline quaternion &operator-=(const quaternion &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }
  inline quaternion &operator+=(const quaternion &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }
  inline quaternion &operator*=(const quaternion &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
  }
  inline quaternion &operator/=(const quaternion &v) {
    RT_ASSERT(!v.isZero(),
              "Division by zero in math::quaternion::this->operator/; Hint : "
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
  bool operator==(const quaternion &v) const {
    return (x == v.x && y == v.y && z == v.z && w == v.w);
  }

  bool operator!=(const quaternion &v) const {
    return (x != v.x || y != v.y || z != v.z || w != v.w);
  }

  inline friend quaternion operator*(f32 factor, const quaternion &u) {
    return quaternion(factor * u.x, factor * u.y, factor * u.z, factor * u.w);
  }

  inline friend quaternion operator-(f32 factor, const quaternion &u) {
    return quaternion(factor - u.x, factor - u.y, factor - u.z, factor - u.w);
  }

  inline friend quaternion operator+(f32 factor, const quaternion &u) {
    return quaternion(factor + u.x, factor + u.y, factor + u.z, factor + u.w);
  }

  inline friend quaternion operator/(f32 factor, const quaternion &u) {
    return quaternion(factor / u.x, factor / u.y, factor / u.z, factor / u.w);
  }

  void invert() {
    x = -x;
    y = -y;
    z = -z;
    w = -w;
  }

  inline f32 scalarProduct(const quaternion &v) const {
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
              "Division by zero in math::quaternion::this->normalize; Hint : "
              "current vector has less than or zero magnitude ");
    *this /= mag;
  }

  inline quaternion normalized() const {
    f32 mag = this->magnitude();
    RT_ASSERT(mag > eps, "cannot normalize zero vector");
    return {x / mag, y / mag, z / mag, w / mag};
  }

  // inline quaternion crossProduct(const quaternion &v) const {
  //   return quaternion((this->y * v.z - this->z * v.y),
  //                  (this->z * v.x - this->x * v.z),
  //                  (this->x * v.y - this->y * v.x));
  // }
  inline f32 dot(const quaternion &v) const {
    return (this->x * v.x) + (this->y * v.y) + (this->z * v.z) +
           (this->w * v.w);
  }

  inline f32 angle(const quaternion &v) const {
    f32 c = (this->dot(v)) / (this->magnitude() * v.magnitude());
    c = std::clamp(c, -1.f, 1.f);
    return std::acos(c);
  }
  inline bool isNormalized() const {
    return std::abs(this->magnitudeSquared() - 1.f) < eps;
  }
  inline f32 distance(const quaternion &v) const {
    f32 x_ = x - v.x;
    f32 y_ = y - v.y;
    f32 z_ = z - v.z;
    f32 w_ = w - v.w;
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
  }
  inline f32 distanceSquared(const quaternion &v) const {
    f32 x_ = x - v.x;
    f32 y_ = y - v.y;
    f32 z_ = z - v.z;
    f32 w_ = w - v.w;
    return (x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
  }
  inline f32 scalarProjection(const quaternion &v) const {
    return this->dot(v) / v.magnitude();
  }
  inline quaternion vectorProjection(const quaternion &v) const {
    return v * (this->dot(v) / (v.magnitude() * v.magnitude()));
  }
  inline quaternion rejectFrom(const quaternion &v) const {
    return *this - this->vectorProjection(v);
  }
  // rotate around a point
  quaternion rotate(const quaternion &axis, f32 angle) const {
    return {
        std::cos(angle / 2.f),
        axis.x * std::sin(angle / 2.f),
        axis.y * std::sin(angle / 2.f),
        axis.z * std::sin(angle / 2.f),
    };
  }
  quaternion reflect(const quaternion &normal) const {
    RT_ASSERT(normal.isNormalized(),
              "Reflection requires a normalized normal.");

    return *this - normal * (2.f * dot(normal));
  }
  bool nearEqual(const quaternion &v) const {
    return std::abs(x - v.x) < eps && std::abs(y - v.y) < eps &&
           std::abs(z - v.z) < eps && std::abs(w - v.w) < eps;
  }
  inline f32 maxComponent() const { return std::max({x, y, z, w}); }
  inline f32 minComponent() const { return std::min({x, y, z, w}); }
  quaternion hadamardProduct(const quaternion &v) const {
    return {x * v.x, y * v.y, z * v.z, w * v.w};
  }
  quaternion clampMagnitude(float maxLength) const {
    float len = magnitude();
    if (len <= maxLength)
      return *this;
    return normalized() * maxLength;
  }

  quaternion refract(const quaternion &normal, float eta) const {
    float cosi = std::clamp(dot(normal), -1.f, 1.f);
    float k = 1.f - eta * eta * (1.f - cosi * cosi);

    if (k < 0)
      return {};
    return (*this) * eta - normal * (eta * cosi + std::sqrt(k));
  }
  quaternion lerp(const quaternion &v, float t) const {
    return *this + (v - *this) * t;
  }
  inline quaternion slerp(quaternion &v, f32 t) const {
    f32 dot = this->dot(v);
    quaternion cv = v;
    if (dot < 0) {
      cv = -v;
      dot = -dot;
    }
    f32 theta = std::acos(std::clamp(dot, -1.f, 1.f));
    if (theta < 0.001)
      return lerp(v, t);
    f32 sintheta = std::sin(theta);
    f32 ratioA = std::sin((1 - t) * theta) / sintheta;
    f32 ratioB = std::sin(t * theta) / sintheta;

    return {x * ratioA + cv.x * ratioB, y * ratioA + cv.y * ratioB,
            z * ratioA + cv.z * ratioB, w * ratioA + cv.w * ratioB};
  }
  Vector3 xyz() const {
    f32 nx = x;
    f32 ny = y;
    f32 nz = z;
    return Vector3(nx, ny, nz);
  }
  Vector2 xy() const {
    f32 nx = x;
    f32 ny = y;
    return Vector2(nx, ny);
  }
};

inline quaternion max(const quaternion &u, const quaternion &v) {
  return quaternion(std::max(u.x, v.x), std::max(u.y, v.y), std::max(u.z, v.z),
                    std::max(u.w, v.w));
}
inline quaternion min(const quaternion &u, const quaternion &v) {
  return quaternion(std::min(u.x, v.x), std::min(u.y, v.y), std::min(u.z, v.z),
                    std::min(u.w, v.w));
}
inline quaternion maxlength(const quaternion &u, const quaternion &v) {
  return u.magnitudeSquared() > v.magnitudeSquared() ? u : v;
}
inline quaternion minlength(const quaternion &u, const quaternion &v) {
  return u.magnitudeSquared() < v.magnitudeSquared() ? u : v;
}

inline quaternion abs(const quaternion &u) {
  return quaternion(std::abs(u.x), std::abs(u.y), std::abs(u.z), std::abs(u.w));
}

inline quaternion ceil(const quaternion &u) {
  return quaternion(std::ceil(u.x), std::ceil(u.y), std::ceil(u.z),
                    std::ceil(u.w));
}
inline quaternion floor(const quaternion &u) {
  return quaternion(std::floor(u.x), std::floor(u.y), std::floor(u.z),
                    std::floor(u.w));
}
inline quaternion round(const quaternion &u) {
  return quaternion(std::round(u.x), std::round(u.y), std::round(u.z),
                    std::round(u.w));
}
}; // namespace math

}; // namespace Engine
