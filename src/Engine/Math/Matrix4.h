#pragma once
#include "Engine/Core/Core.h"
#include "Engine/Math/Matrix3.h"
#include "Engine/Math/Vector3.h"
#include "Engine/Math/Vector4.h"
#include <cmath>

namespace Engine {
namespace math {

struct Matrix4 {
  f32 data[4][4] = {{0.f, 0.f, 0.f, 0.f},
                    {0.f, 0.f, 0.f, 0.f},
                    {0.f, 0.f, 0.f, 0.f},
                    {0.f, 0.f, 0.f, 0.f}};

  explicit Matrix4() = default;

  explicit Matrix4(f32 d00, f32 d01, f32 d02, f32 d03, f32 d10, f32 d11,
                   f32 d12, f32 d13, f32 d20, f32 d21, f32 d22, f32 d23,
                   f32 d30, f32 d31, f32 d32, f32 d33) {
    data[0][0] = d00;
    data[0][1] = d01;
    data[0][2] = d02;
    data[0][3] = d03;
    data[1][0] = d10;
    data[1][1] = d11;
    data[1][2] = d12;
    data[1][3] = d13;
    data[2][0] = d20;
    data[2][1] = d21;
    data[2][2] = d22;
    data[2][3] = d23;
    data[3][0] = d30;
    data[3][1] = d31;
    data[3][2] = d32;
    data[3][3] = d33;
  }

  // Column-vector convention: c0..c3 are COLUMNS of the matrix
  // (matches Matrix3's vector-constructor convention).
  explicit Matrix4(const Vector4 &c0, const Vector4 &c1, const Vector4 &c2,
                   const Vector4 &c3) {
    data[0][0] = c0.x;
    data[0][1] = c1.x;
    data[0][2] = c2.x;
    data[0][3] = c3.x;
    data[1][0] = c0.y;
    data[1][1] = c1.y;
    data[1][2] = c2.y;
    data[1][3] = c3.y;
    data[2][0] = c0.z;
    data[2][1] = c1.z;
    data[2][2] = c2.z;
    data[2][3] = c3.z;
    data[3][0] = c0.w;
    data[3][1] = c1.w;
    data[3][2] = c2.w;
    data[3][3] = c3.w;
  }

  explicit Matrix4(const f32 val) {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        data[i][j] = val;
  }

  explicit Matrix4(const Matrix3 &m) {
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        data[i][j] = m[i][j];
    data[3][3] = 1.f;
  }

  f32 *operator[](int row) {
    if (row < 0 || row >= 4)
      throw std::out_of_range("Matrix4 row index out of range");
    return data[row];
  }
  const f32 *operator[](int row) const {
    if (row < 0 || row >= 4)
      throw std::out_of_range("Matrix4 row index out of range");
    return data[row];
  }

  bool operator==(const Matrix4 &m) const {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        if (data[i][j] != m.data[i][j])
          return false;
    return true;
  }
  bool operator!=(const Matrix4 &m) const { return !(*this == m); }

  Matrix4 operator-() const {
    Matrix4 result;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        result.data[i][j] = -data[i][j];
    return result;
  }

  [[nodiscard]] inline Matrix4 operator*(f32 scalar) const {
    Matrix4 ret(*this);
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        ret.data[i][j] *= scalar;
    return ret;
  }
  inline Matrix4 operator/(f32 scalar) const {
    RT_ASSERT(std::abs(scalar) > eps, "Scalar value cannot be zero");
    Matrix4 ret(*this);
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        ret.data[i][j] /= scalar;
    return ret;
  }
  inline Matrix4 &operator*=(f32 scalar) {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        data[i][j] *= scalar;
    return *this;
  }
  inline Matrix4 &operator/=(f32 scalar) {
    RT_ASSERT(std::abs(scalar) > eps, "Scalar value cannot be zero");
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        data[i][j] /= scalar;
    return *this;
  }

  [[nodiscard]] inline Matrix4 operator+(const Matrix4 &v) const {
    Matrix4 ret;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        ret.data[i][j] = data[i][j] + v.data[i][j];
    return ret;
  }
  [[nodiscard]] inline Matrix4 operator-(const Matrix4 &v) const {
    Matrix4 ret;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        ret.data[i][j] = data[i][j] - v.data[i][j];
    return ret;
  }
  inline Matrix4 &operator+=(const Matrix4 &v) {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        data[i][j] += v.data[i][j];
    return *this;
  }
  inline Matrix4 &operator-=(const Matrix4 &v) {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        data[i][j] -= v.data[i][j];
    return *this;
  }

  [[nodiscard]] inline Matrix4 operator*(const Matrix4 &v) const {
    Matrix4 c;
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        f32 sum = 0.f;
        for (int k = 0; k < 4; ++k)
          sum += data[i][k] * v.data[k][j];
        c.data[i][j] = sum;
      }
    }
    return c;
  }
  inline Matrix4 &operator*=(const Matrix4 &v) {
    *this = *this * v;
    return *this;
  }

  [[nodiscard]] inline Vector4 operator*(const Vector4 &a) const {
    return Vector4(data[0][0] * a.x + data[0][1] * a.y + data[0][2] * a.z +
                       data[0][3] * a.w,
                   data[1][0] * a.x + data[1][1] * a.y + data[1][2] * a.z +
                       data[1][3] * a.w,
                   data[2][0] * a.x + data[2][1] * a.y + data[2][2] * a.z +
                       data[2][3] * a.w,
                   data[3][0] * a.x + data[3][1] * a.y + data[3][2] * a.z +
                       data[3][3] * a.w);
  }

  inline Vector3 transformPoint(const Vector3 &p) const {
    Vector4 r = (*this) * Vector4(p.x, p.y, p.z, 1.f);
    RT_ASSERT(std::abs(r.w) > eps, "transformPoint produced w == 0");
    return Vector3(r.x / r.w, r.y / r.w, r.z / r.w);
  }
  inline Vector3 transformVector(const Vector3 &v) const {
    Vector4 r = (*this) * Vector4(v.x, v.y, v.z, 0.f);
    return Vector3(r.x, r.y, r.z);
  }

  friend Matrix4 operator*(f32 s, const Matrix4 &m) { return m * s; }
  friend Matrix4 operator/(f32 s, const Matrix4 &m) { return m / s; }

  [[nodiscard]] Matrix4 transposed() const {
    Matrix4 result(*this);
    result.transpose();
    return result;
  }
  inline Matrix4 &transpose() {
    for (int i = 0; i < 4; ++i)
      for (int j = i + 1; j < 4; ++j)
        std::swap(data[i][j], data[j][i]);
    return *this;
  }

  inline f32 minorDet3(int r0, int r1, int r2, int c0, int c1, int c2) const {
    return data[r0][c0] *
               (data[r1][c1] * data[r2][c2] - data[r1][c2] * data[r2][c1]) -
           data[r0][c1] *
               (data[r1][c0] * data[r2][c2] - data[r1][c2] * data[r2][c0]) +
           data[r0][c2] *
               (data[r1][c0] * data[r2][c1] - data[r1][c1] * data[r2][c0]);
  }

  inline f32 determinant() const {
    f32 det = 0.f;
    static const int rows[3] = {1, 2, 3};
    int cols[3];
    f32 sign = 1.f;
    for (int col = 0; col < 4; ++col) {
      int idx = 0;
      for (int c = 0; c < 4; ++c)
        if (c != col)
          cols[idx++] = c;
      f32 minor =
          minorDet3(rows[0], rows[1], rows[2], cols[0], cols[1], cols[2]);
      det += sign * data[0][col] * minor;
      sign = -sign;
    }
    return det;
  }

  [[nodiscard]] inline Matrix4 cofactor() const {
    Matrix4 result;
    for (int i = 0; i < 4; ++i) {
      int rr[3];
      int ri = 0;
      for (int r = 0; r < 4; ++r)
        if (r != i)
          rr[ri++] = r;
      for (int j = 0; j < 4; ++j) {
        int cc[3];
        int ci = 0;
        for (int c = 0; c < 4; ++c)
          if (c != j)
            cc[ci++] = c;
        f32 minor = minorDet3(rr[0], rr[1], rr[2], cc[0], cc[1], cc[2]);
        f32 sign = ((i + j) % 2 == 0) ? 1.f : -1.f;
        result.data[i][j] = sign * minor;
      }
    }
    return result;
  }

  [[nodiscard]] inline Matrix4 adjugated() const {
    return this->cofactor().transposed();
  }

  [[nodiscard]] inline Matrix4 inversed() const {
    f32 det = determinant();
    RT_ASSERT(std::abs(det) > eps, "Matrix is singular.");
    return this->adjugated() * (1.f / det);
  }
  inline Matrix4 inverse() const { return inversed(); }

  [[nodiscard]] Matrix4 rigidInverse() const {
    Matrix3 R(data[0][0], data[0][1], data[0][2], data[1][0], data[1][1],
              data[1][2], data[2][0], data[2][1], data[2][2]);
    // NOTE: Matrix3's vector-constructor is column-based; direct element
    // construction above is safe since we're filling via the (row,col) ctor.
    Matrix3 Rt = R.transposed();
    Vector3 t(data[0][3], data[1][3], data[2][3]);
    Vector3 nt = Rt * (t * -1.f);

    Matrix4 result(Rt);
    result.data[0][3] = nt.x;
    result.data[1][3] = nt.y;
    result.data[2][3] = nt.z;
    result.data[3][3] = 1.f;
    return result;
  }

  inline f32 trace() const {
    f32 t = 0.f;
    for (int i = 0; i < 4; ++i)
      t += data[i][i];
    return t;
  }

  static Matrix4 identity() {
    return Matrix4(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
                   0.f, 0.f, 0.f, 1.f);
  }
  static Matrix4 zero() { return Matrix4(); }

  static Matrix4 translation(const Vector3 &t) {
    return Matrix4(1.f, 0.f, 0.f, t.x, 0.f, 1.f, 0.f, t.y, 0.f, 0.f, 1.f, t.z,
                   0.f, 0.f, 0.f, 1.f);
  }

  static Matrix4 scale(const Vector3 &s) {
    return Matrix4(s.x, 0.f, 0.f, 0.f, 0.f, s.y, 0.f, 0.f, 0.f, 0.f, s.z, 0.f,
                   0.f, 0.f, 0.f, 1.f);
  }

  static Matrix4 rotateX(f32 radians) {
    f32 c = std::cos(radians), s = std::sin(radians);
    return Matrix4(1.f, 0.f, 0.f, 0.f, 0.f, c, -s, 0.f, 0.f, s, c, 0.f, 0.f,
                   0.f, 0.f, 1.f);
  }
  static Matrix4 rotateY(f32 radians) {
    f32 c = std::cos(radians), s = std::sin(radians);
    return Matrix4(c, 0.f, s, 0.f, 0.f, 1.f, 0.f, 0.f, -s, 0.f, c, 0.f, 0.f,
                   0.f, 0.f, 1.f);
  }
  static Matrix4 rotateZ(f32 radians) {
    f32 c = std::cos(radians), s = std::sin(radians);
    return Matrix4(c, -s, 0.f, 0.f, s, c, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
                   0.f, 0.f, 1.f);
  }

  static Matrix4 rotateAxisAngle(const Vector3 &axis, f32 radians) {
    RT_ASSERT(axis.isNormalized(),
              "rotateAxisAngle requires a normalized axis");
    f32 c = std::cos(radians), s = std::sin(radians), t = 1.f - c;
    f32 x = axis.x, y = axis.y, z = axis.z;
    return Matrix4(t * x * x + c, t * x * y - s * z, t * x * z + s * y, 0.f,
                   t * x * y + s * z, t * y * y + c, t * y * z - s * x, 0.f,
                   t * x * z - s * y, t * y * z + s * x, t * z * z + c, 0.f,
                   0.f, 0.f, 0.f, 1.f);
  }

  static Matrix4 trs(const Vector3 &translationV, const Matrix4 &rotate,
                     const Vector3 &scaleV) {
    return translation(translationV) * rotate * scale(scaleV);
  }

  static Matrix4 lookAt(const Vector3 &eye, const Vector3 &target,
                        const Vector3 &up) {
    Vector3 f = (target - eye).normalized();     // forward
    Vector3 s = f.crossProduct(up).normalized(); // right
    Vector3 u = s.crossProduct(f);               // recomputed up

    Matrix4 result = identity();
    result.data[0][0] = s.x;
    result.data[0][1] = s.y;
    result.data[0][2] = s.z;
    result.data[1][0] = u.x;
    result.data[1][1] = u.y;
    result.data[1][2] = u.z;
    result.data[2][0] = -f.x;
    result.data[2][1] = -f.y;
    result.data[2][2] = -f.z;
    result.data[0][3] = -s.dot(eye);
    result.data[1][3] = -u.dot(eye);
    result.data[2][3] = f.dot(eye);
    return result;
  }

  static Matrix4 perspective(f32 fovYRadians, f32 aspect, f32 nearZ, f32 farZ) {
    RT_ASSERT(std::abs(aspect) > eps, "aspect ratio cannot be zero");
    f32 tanHalfFov = std::tan(fovYRadians * 0.5f);
    Matrix4 result = zero();
    result.data[0][0] = 1.f / (aspect * tanHalfFov);
    result.data[1][1] = 1.f / tanHalfFov;
    result.data[2][2] = -(farZ + nearZ) / (farZ - nearZ);
    result.data[2][3] = -(2.f * farZ * nearZ) / (farZ - nearZ);
    result.data[3][2] = -1.f;
    return result;
  }

  static Matrix4 orthographic(f32 left, f32 right, f32 bottom, f32 top,
                              f32 nearZ, f32 farZ) {
    Matrix4 result = identity();
    result.data[0][0] = 2.f / (right - left);
    result.data[1][1] = 2.f / (top - bottom);
    result.data[2][2] = -2.f / (farZ - nearZ);
    result.data[0][3] = -(right + left) / (right - left);
    result.data[1][3] = -(top + bottom) / (top - bottom);
    result.data[2][3] = -(farZ + nearZ) / (farZ - nearZ);
    return result;
  }

  [[nodiscard]] Matrix3 normalMatrix() const {
    Matrix3 upper3x3(data[0][0], data[0][1], data[0][2], data[1][0], data[1][1],
                     data[1][2], data[2][0], data[2][1], data[2][2]);
    return upper3x3.inverse().transposed();
  }
};

}; // namespace math
}; // namespace Engine
