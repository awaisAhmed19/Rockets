#pragma once
#include "Engine/Math/Vector2.h"
#include "Engine/core/core.h"
namespace Engine {
namespace math {
struct Matrix2 {
  f32 data[2][2] = {{0.f, 0.f}, {0.f, 0.f}};
  Matrix2() = default;
  Matrix2(f32 data00, f32 data01, f32 data10, f32 data11) {
    data[0][0] = data00;
    data[0][1] = data01;
    data[1][0] = data10;
    data[1][1] = data11;
  }

  Matrix2(const Vector2 &data1, const Vector2 &data2) {
    data[0][0] = data1.x;
    data[0][1] = data2.x;
    data[1][0] = data1.y;
    data[1][1] = data2.y;
  }

  explicit Matrix2(const f32 val) {
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        data[i][j] = val;
      }
    }
  }
  f32 *operator[](int row) {
    if (row < 0 || row >= 2) {
      throw std::out_of_range("Matrix2 row index out of range");
    }
    return data[row];
  }
  const f32 *operator[](int row) const {
    if (row < 0 || row >= 2) {
      throw std::out_of_range("Matrix2 row index out of range");
    }
    return data[row];
  }
  bool operator==(const Matrix2 &mat) const {
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        if (data[i][j] != mat.data[i][j])
          return false;
      }
    }
    return true;
  };
  bool operator!=(const Matrix2 &mat) const { return !(*this == mat); }
  Matrix2 operator-() const {
    Matrix2 result;

    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < 2; ++j)
        result.data[i][j] = -data[i][j];

    return result;
  }
  inline Matrix2 operator*(f32 scalar) const {
    Matrix2 ret(*this);
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        ret.data[i][j] *= scalar;
      }
    }
    return ret;
  }
  inline Matrix2 operator/(f32 scalar) const {
    RT_ASSERT(std::abs(scalar) > eps, "Scalar value cannot be zero");
    Matrix2 ret(*this);
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        ret.data[i][j] /= scalar;
      }
    }
    return ret;
  }
  inline Matrix2 &operator*=(f32 scalar) {
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        data[i][j] *= scalar;
      }
    }
    return *this;
  }
  inline Matrix2 &operator/=(f32 scalar) {
    RT_ASSERT(std::abs(scalar) > eps, "Scalar value cannot be zero");
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        data[i][j] /= scalar;
      }
    }
    return *this;
  }
  inline Matrix2 operator+(const Matrix2 &v) const {
    return Matrix2(data[0][0] + v.data[0][0], data[0][1] + v.data[0][1],
                   data[1][0] + v.data[1][0], data[1][1] + v.data[1][1]);
  }
  inline Matrix2 operator-(const Matrix2 &v) const {
    return Matrix2(data[0][0] - v.data[0][0], data[0][1] - v.data[0][1],
                   data[1][0] - v.data[1][0], data[1][1] - v.data[1][1]);
  }
  inline Matrix2 operator*(const Matrix2 &v) const {
    Matrix2 c;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        c[i][j] = 0;

        for (int k = 0; k < 2; ++k)
          c[i][j] += data[i][k] * v[k][j];
      }
    }
    return c;
  }
  inline Matrix2 &operator+=(const Matrix2 &v) {
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        data[i][j] += v.data[i][j];
      }
    }
    return *this;
  }
  inline Matrix2 &operator-=(const Matrix2 &v) {
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        data[i][j] -= v.data[i][j];
      }
    }
    return *this;
  }
  inline Matrix2 &operator*=(const Matrix2 &v) {
    *this = *this * v;
    return *this;
  }
  Vector2 operator*(const Vector2 &a) const {
    return Vector2(data[0][0] * a.x + data[0][1] * a.y,
                   data[1][0] * a.x + data[1][1] * a.y);
  }
  friend Matrix2 operator*(f32 s, const Matrix2 &m) { return m * s; }
  friend Matrix2 operator/(f32 s, const Matrix2 &m) { return m / s; }

  // transposed()
  [[nodiscard]] Matrix2 transposed() const {
    Matrix2 result(*this);
    result.transpose();
    return result;
  }

  // transpose()
  inline Matrix2 &transpose() {
    for (int i = 0; i < 2; ++i) {
      for (int j = i + 1; j < 2; ++j) {
        std::swap(data[i][j], data[j][i]);
      }
    }
    return *this;
  }
  // determinant()
  inline f32 determinant() const {
    const f32 minor00 = data[0][0] * data[1][1] - data[1][0] * data[0][1];
    return minor00;
  }

  [[nodiscard]] inline Matrix2 swapnegate() const {
    return Matrix2(data[1][1], -data[0][1], -data[1][0], data[0][0]);
  }

  [[nodiscard]] inline Matrix2 cofactor() const { return this->swapnegate(); }

  inline Matrix2 cofactored() const {
    Matrix2 result(*this);
    return result.cofactor();
  }
  [[nodiscard]] inline Matrix2 adjugated() const { return this->cofactor(); }
  inline Matrix2 adjugate() const {
    Matrix2 ret(*this);
    return ret.adjugated();
  }
  // inverse()
  [[nodiscard]] inline Matrix2 inversed() const {
    f32 det = determinant();
    RT_ASSERT(std::abs(det) > eps, "Matrix is singular.");
    return this->adjugate() * (1.f / det);
  }

  inline Matrix2 inverse() const {
    Matrix2 ret(*this);
    return ret.inversed();
  }

  // trace()
  inline f32 trace() const {
    f32 trace = 0.f;
    for (int i = 0; i < 2; ++i) {
      trace += data[i][i];
    }
    return trace;
  }
  static Matrix2 identity() { return Matrix2(1.f, 0.f, 0.f, 1.f); }
  static Matrix2 zero() { return Matrix2(); }
};
}; // namespace math
}; // namespace Engine
