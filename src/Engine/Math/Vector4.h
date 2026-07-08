
#pragma once
#include "Engine/Core/Core.h"
#include "Engine/Math/Constants.h"
#include "Engine/Math/Vector2.h"
#include "Engine/Math/Vector3.h"
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
[X] perpendicular() (Vector4)
[X] rotate() (Vector4)
[X] rotateAround() (Vector4)
[X] tripleProduct() (Vector4)
//contact math
[ ] reflect()
[ ] refract()
*/
struct Vector4 {
  f32 x = 0.f;
  f32 y = 0.f;
  f32 z = 0.f;
  f32 w = 0.f;

  constexpr Vector4() = default;
  constexpr Vector4(f32 _x, f32 _y, f32 _z, f32 _w)
      : x(_x), y(_y), z(_z), w(_w) {}
  f32 &operator[](int i) { return ((&x)[i]); }
  const f32 &operator[](int i) const { return ((&x)[i]); }
  inline Vector4 operator*(const f32 scalar) const {
    return (Vector4(x * scalar, y * scalar, z * scalar, w * scalar));
  }

  inline Vector4 operator+(const f32 scalar) {
    return (Vector4(x + scalar, y + scalar, z + scalar, w + scalar));
  }

  inline Vector4 operator-(const f32 scalar) {
    return (Vector4(x - scalar, y - scalar, z - scalar, w - scalar));
  }
  inline Vector4 operator-(const Vector4 &v) const {
    return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
  }
  inline Vector4 operator+(const Vector4 &v) const {
    return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
  }
  inline Vector4 operator*(const Vector4 &v) const {
    return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
  }
  inline Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }

  inline Vector4 operator/(const Vector4 &v) const {
    RT_ASSERT(!v.isZero(),
              "Division by zero in math::Vector4::this->operator/; Hint : "
              "check your input vector u/ v/ <- ");
    return Vector4(x / v.x, y / v.y, z / v.z, w / v.w);
  }

  inline Vector4 &operator*=(const f32 scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return (*this);
  }

  inline Vector4 &operator/=(f32 scalar) {
    scalar = 1.f / scalar;
    RT_ASSERT(std::abs(scalar) > eps,
              "scalar less than or equal to zero in /= scalar");
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return (*this);
  }

  inline Vector4 &operator-=(const Vector4 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }
  inline Vector4 &operator+=(const Vector4 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }
  inline Vector4 &operator*=(const Vector4 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
  }
  inline Vector4 &operator/=(const Vector4 &v) {
    RT_ASSERT(!v.isZero(),
              "Division by zero in math::Vector4::this->operator/; Hint : "
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
  bool operator==(const Vector4 &v) const {
    return (x == v.x && y == v.y && z == v.z && w == v.w);
  }

  bool operator!=(const Vector4 &v) const {
    return (x != v.x || y != v.y || z != v.z || w != v.w);
  }

  inline friend Vector4 operator*(f32 factor, const Vector4 &u) {
    return Vector4(factor * u.x, factor * u.y, factor * u.z, factor * u.w);
  }

  inline friend Vector4 operator-(f32 factor, const Vector4 &u) {
    return Vector4(factor - u.x, factor - u.y, factor - u.z, factor - u.w);
  }

  inline friend Vector4 operator+(f32 factor, const Vector4 &u) {
    return Vector4(factor + u.x, factor + u.y, factor + u.z, factor + u.w);
  }

  inline friend Vector4 operator/(f32 factor, const Vector4 &u) {
    return Vector4(factor / u.x, factor / u.y, factor / u.z, factor / u.w);
  }

  void invert() {
    x = -x;
    y = -y;
    z = -z;
    w = -w;
  }

  inline f32 scalarProduct(const Vector4 &v) const {
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
              "Division by zero in math::Vector4::this->normalize; Hint : "
              "current vector has less than or zero magnitude ");
    *this /= mag;
  }

  inline Vector4 normalized() const {
    f32 mag = this->magnitude();
    RT_ASSERT(mag > eps, "cannot normalize zero vector");
    return {x / mag, y / mag, z / mag, w / mag};
  }

  // inline Vector4 crossProduct(const Vector4 &v) const {
  //   return Vector4((this->y * v.z - this->z * v.y),
  //                  (this->z * v.x - this->x * v.z),
  //                  (this->x * v.y - this->y * v.x));
  // }
  inline f32 dot(const Vector4 &v) const {
    return (this->x * v.x) + (this->y * v.y) + (this->z * v.z) +
           (this->w * v.w);
  }

  inline f32 angle(const Vector4 &v) const {
    f32 c = (this->dot(v)) / (this->magnitude() * v.magnitude());
    c = std::clamp(c, -1.f, 1.f);
    return std::acos(c);
  }
  inline bool isNormalized() const {
    return std::abs(this->magnitudeSquared() - 1.f) < eps;
  }
  inline f32 distance(const Vector4 &v) const {
    f32 x_ = x - v.x;
    f32 y_ = y - v.y;
    f32 z_ = z - v.z;
    f32 w_ = w - v.w;
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
  }
  inline f32 distanceSquared(const Vector4 &v) const {
    f32 x_ = x - v.x;
    f32 y_ = y - v.y;
    f32 z_ = z - v.z;
    f32 w_ = w - v.w;
    return (x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
  }
  inline f32 scalarProjection(const Vector4 &v) const {
    return this->dot(v) / v.magnitude();
  }
  inline Vector4 vectorProjection(const Vector4 &v) const {
    return v * (this->dot(v) / (v.magnitude() * v.magnitude()));
  }
  inline Vector4 rejectFrom(const Vector4 &v) const {
    return *this - this->vectorProjection(v);
  }
  // rotate around a point
  Vector4 rotateAround(const Vector4 &point, const Vector4 &axis,
                       float radians) const;
  Vector4 reflect(const Vector4 &normal) const {
    RT_ASSERT(normal.isNormalized(),
              "Reflection requires a normalized normal.");

    return *this - normal * (2.f * dot(normal));
  }
  bool nearEqual(const Vector4 &v) const {
    return std::abs(x - v.x) < eps && std::abs(y - v.y) < eps &&
           std::abs(z - v.z) < eps && std::abs(w - v.w) < eps;
  }
  inline f32 maxComponent() const { return std::max({x, y, z, w}); }
  inline f32 minComponent() const { return std::min({x, y, z, w}); }
  Vector4 hadamardProduct(const Vector4 &v) const {
    return {x * v.x, y * v.y, z * v.z, w * v.w};
  }
  Vector4 clampMagnitude(float maxLength) const {
    float len = magnitude();
    if (len <= maxLength)
      return *this;
    return normalized() * maxLength;
  }

  Vector4 refract(const Vector4 &normal, float eta) const {
    float cosi = std::clamp(dot(normal), -1.f, 1.f);
    float k = 1.f - eta * eta * (1.f - cosi * cosi);

    if (k < 0)
      return {};
    return (*this) * eta - normal * (eta * cosi + std::sqrt(k));
  }
  Vector4 lerp(const Vector4 &v, float t) const {
    return *this + (v - *this) * t;
  }
  inline Vector4 slerp(Vector4 &v, f32 t) const {
    f32 dot = this->dot(v);
    Vector4 cv = v;
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

inline Vector4 max(const Vector4 &u, const Vector4 &v) {
  return Vector4(std::max(u.x, v.x), std::max(u.y, v.y), std::max(u.z, v.z),
                 std::max(u.w, v.w));
}
inline Vector4 min(const Vector4 &u, const Vector4 &v) {
  return Vector4(std::min(u.x, v.x), std::min(u.y, v.y), std::min(u.z, v.z),
                 std::min(u.w, v.w));
}
inline Vector4 maxlength(const Vector4 &u, const Vector4 &v) {
  return u.magnitudeSquared() > v.magnitudeSquared() ? u : v;
}
inline Vector4 minlength(const Vector4 &u, const Vector4 &v) {
  return u.magnitudeSquared() < v.magnitudeSquared() ? u : v;
}

inline Vector4 abs(const Vector4 &u) {
  return Vector4(std::abs(u.x), std::abs(u.y), std::abs(u.z), std::abs(u.w));
}

inline Vector4 ceil(const Vector4 &u) {
  return Vector4(std::ceil(u.x), std::ceil(u.y), std::ceil(u.z),
                 std::ceil(u.w));
}
inline Vector4 floor(const Vector4 &u) {
  return Vector4(std::floor(u.x), std::floor(u.y), std::floor(u.z),
                 std::floor(u.w));
}
inline Vector4 round(const Vector4 &u) {
  return Vector4(std::round(u.x), std::round(u.y), std::round(u.z),
                 std::round(u.w));
}
}; // namespace math

}; // namespace Engine
