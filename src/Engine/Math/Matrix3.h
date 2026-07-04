#pragma once
#include "Engine/Math/Vector3.h"
#include "Engine/core/core.h"
namespace Engine {
namespace math {
struct Matrix3 {
  f32 data[3][3] = {{0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}};
  explicit Matrix3() = default;
  explicit Matrix3(f32 data00, f32 data01, f32 data02, f32 data10, f32 data11,
                   f32 data12, f32 data20, f32 data21, f32 data22) {
    data[0][0] = data00;
    data[0][1] = data01;
    data[0][2] = data02;
    data[1][0] = data10;
    data[1][1] = data11;
    data[1][2] = data12;
    data[2][0] = data20;
    data[2][1] = data21;
    data[2][2] = data22;
  }
  explicit Matrix3(const Vector3 &data1, const Vector3 &data2,
                   const Vector3 &data3) {
    data[0][0] = data1.x;
    data[0][1] = data2.x;
    data[0][2] = data3.x;
    data[1][0] = data1.y;
    data[1][1] = data2.y;
    data[1][2] = data3.y;
    data[2][0] = data1.z;
    data[2][1] = data2.z;
    data[2][2] = data3.z;
  }

  explicit Matrix3(const f32 val) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        data[i][j] = val;
      }
    }
  }

  f32 *operator[](int row) {
    if (row < 0 || row >= 3) {
      throw std::out_of_range("Matrix3 row index out of range");
    }
    return data[row];
  }
  const f32 *operator[](int row) const {
    if (row < 0 || row >= 3) {
      throw std::out_of_range("Matrix3 row index out of range");
    }
    return data[row];
  }
  bool operator==(const Matrix3 &mat) const {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (data[i][j] != mat.data[i][j])
          return false;
      }
    }
    return true;
  };
  bool operator!=(const Matrix3 &mat) const { return !(*this == mat); }
  Matrix3 operator-() const {
    Matrix3 result;

    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        result.data[i][j] = -data[i][j];

    return result;
  }
  [[nodiscard]] inline Matrix3 operator*(f32 scalar) const {
    Matrix3 ret(*this);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        ret.data[i][j] *= scalar;
      }
    }
    return ret;
  }
  [[nodiscard]] inline Matrix3 operator/(f32 scalar) const {
    RT_ASSERT(std::abs(scalar) > eps, "Scalar value cannot be zero");
    Matrix3 ret(*this);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        ret.data[i][j] /= scalar;
      }
    }
    return ret;
  }
  inline Matrix3 &operator*=(f32 scalar) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        data[i][j] *= scalar;
      }
    }
    return *this;
  }
  inline Matrix3 &operator/=(f32 scalar) {
    RT_ASSERT(std::abs(scalar) > eps, "Scalar value cannot be zero");
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        data[i][j] /= scalar;
      }
    }
    return *this;
  }
  [[nodiscard]] inline Matrix3 operator+(const Matrix3 &v) const {
    return Matrix3(data[0][0] + v.data[0][0], data[0][1] + v.data[0][1],
                   data[0][2] + v.data[0][2], data[1][0] + v.data[1][0],
                   data[1][1] + v.data[1][1], data[1][2] + v.data[1][2],
                   data[2][0] + v.data[2][0], data[2][1] + v.data[2][1],
                   data[2][2] + v.data[2][2]);
  }
  [[nodiscard]] inline Matrix3 operator-(const Matrix3 &v) const {
    return Matrix3(data[0][0] - v.data[0][0], data[0][1] - v.data[0][1],
                   data[0][2] - v.data[0][2], data[1][0] - v.data[1][0],
                   data[1][1] - v.data[1][1], data[1][2] - v.data[1][2],
                   data[2][0] - v.data[2][0], data[2][1] - v.data[2][1],
                   data[2][2] - v.data[2][2]);
  }
  [[nodiscard]] inline Matrix3 operator*(const Matrix3 &v) const {
    Matrix3 c;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        c[i][j] = 0;

        for (int k = 0; k < 3; ++k)
          c[i][j] += data[i][k] * v[k][j];
      }
    }
    return c;
  }
  inline Matrix3 &operator+=(const Matrix3 &v) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        data[i][j] += v.data[i][j];
      }
    }
    return *this;
  }
  inline Matrix3 &operator-=(const Matrix3 &v) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        data[i][j] -= v.data[i][j];
      }
    }
    return *this;
  }
  inline Matrix3 &operator*=(const Matrix3 &v) {
    *this = *this * v;
    return *this;
  }
  [[nodiscard]] Vector3 operator*(const Vector3 &a) const {
    return Vector3(data[0][0] * a.x + data[0][1] * a.y + data[0][2] * a.z,
                   data[1][0] * a.x + data[1][1] * a.y + data[1][2] * a.z,
                   data[2][0] * a.x + data[2][1] * a.y + data[2][2] * a.z);
  }
  friend Matrix3 operator*(f32 s, const Matrix3 &m) { return m * s; }
  friend Matrix3 operator/(f32 s, const Matrix3 &m) { return m / s; }

  // transposed()
  [[nodiscard]] Matrix3 transposed() const {
    Matrix3 result(*this);
    result.transpose();
    return result;
  }

  // transpose()
  inline Matrix3 &transpose() {
    for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 3; ++j) {
        std::swap(data[i][j], data[j][i]);
      }
    }
    return *this;
  }
  // determinant()
  inline f32 determinant() const {
    const f32 minor00 = data[1][1] * data[2][2] - data[1][2] * data[2][1];
    const f32 minor01 = data[1][0] * data[2][2] - data[1][2] * data[2][0];
    const f32 minor02 = data[1][0] * data[2][1] - data[1][1] * data[2][0];

    return data[0][0] * minor00 - data[0][1] * minor01 + data[0][2] * minor02;
  }

  [[nodiscard]] inline Matrix3 minors() const {
    const f32 m00 = data[1][1] * data[2][2] - data[1][2] * data[2][1];
    const f32 m01 = data[1][0] * data[2][2] - data[1][2] * data[2][0];
    const f32 m02 = data[1][0] * data[2][1] - data[1][1] * data[2][0];
    const f32 m10 = data[0][1] * data[2][2] - data[0][2] * data[2][1];
    const f32 m11 = data[0][0] * data[2][2] - data[0][2] * data[2][0];
    const f32 m12 = data[0][0] * data[2][1] - data[0][1] * data[2][0];
    const f32 m20 = data[0][1] * data[1][2] - data[1][1] * data[0][2];
    const f32 m21 = data[0][0] * data[1][2] - data[1][0] * data[0][2];
    const f32 m22 = data[0][0] * data[1][1] - data[1][0] * data[0][1];
    return Matrix3(m00, m01, m02, m10, m11, m12, m20, m21, m22);
  }

  [[nodiscard]] inline Matrix3 cofactor() const {
    Matrix3 minors(this->minors());
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        const float sign = ((i + j) % 2 == 0) ? 1.f : -1.f;
        minors.data[i][j] = sign * minors.data[i][j];
      }
    }
    return minors;
  }

  inline Matrix3 cofactored() const {
    Matrix3 result(*this);
    return result.cofactor();
  }
  [[nodiscard]] inline Matrix3 adjugated() const {
    return this->cofactor().transposed();
  }
  inline Matrix3 adjugate() const {
    Matrix3 ret(*this);
    return ret.adjugated();
  }
  // inverse()
  [[nodiscard]] inline Matrix3 inversed() const {
    f32 det = determinant();
    RT_ASSERT(std::abs(det) > eps, "Matrix is singular.");
    return this->adjugate() * (1.f / det);
  }

  inline Matrix3 inverse() const {
    Matrix3 ret(*this);
    return ret.inversed();
  }

  // trace()
  inline f32 trace() const {
    f32 trace = 0.f;
    for (int i = 0; i < 3; ++i) {
      trace += data[i][i];
    }
    return trace;
  }
  static Matrix3 identity() {
    return Matrix3(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f);
  }

  static Matrix3 zero() { return Matrix3(); }
};
}; // namespace math
}; // namespace Engine
