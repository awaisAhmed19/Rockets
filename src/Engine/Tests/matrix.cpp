#include "Engine/Math/Matrix.h"
#include "Engine/core/Tester.h"
using namespace Engine::math;

TEST_CASE("matrixN construction via initializer list") {
  Matrix<f32, 2, 3> m{{1.f, 2.f, 3.f}, {4.f, 5.f, 6.f}};
  CHECK_NEAR(m[0][0], 1.f, 1e-6f);
  CHECK_NEAR(m[1][2], 6.f, 1e-6f);
}

TEST_CASE("matrixN identity is only valid for square matrices") {
  auto id = Matrix<f32, 3, 3>::identity();
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      CHECK_NEAR(id[i][j], (i == j) ? 1.f : 0.f, 1e-6f);
}

TEST_CASE("matrixN non-square multiply produces correct shape and values") {
  Matrix<f32, 2, 3> a{{1.f, 2.f, 3.f}, {4.f, 5.f, 6.f}};
  Matrix<f32, 3, 2> b{{7.f, 8.f}, {9.f, 10.f}, {11.f, 12.f}};
  auto c = a * b; // 2x2 result
  // row0: [1*7+2*9+3*11, 1*8+2*10+3*12] = [58, 64]
  // row1: [4*7+5*9+6*11, 4*8+5*10+6*12] = [139, 154]
  CHECK_NEAR(c[0][0], 58.f, 1e-4f);
  CHECK_NEAR(c[0][1], 64.f, 1e-4f);
  CHECK_NEAR(c[1][0], 139.f, 1e-4f);
  CHECK_NEAR(c[1][1], 154.f, 1e-4f);
}

TEST_CASE("matrixN matrix-vector multiply, column-vector convention") {
  Matrix<f32, 2, 2> m{{1.f, 2.f}, {3.f, 4.f}};
  std::array<f32, 2> v{5.f, 6.f};
  auto r = m * v;
  CHECK_NEAR(r[0], 1.f * 5.f + 2.f * 6.f, 1e-5f);
  CHECK_NEAR(r[1], 3.f * 5.f + 4.f * 6.f, 1e-5f);
}

TEST_CASE("matrixN transpose swaps rows and columns and shape") {
  Matrix<f32, 2, 3> m{{1.f, 2.f, 3.f}, {4.f, 5.f, 6.f}};
  Matrix<f32, 3, 2> t = m.transposed();
  CHECK_NEAR(t[0][0], 1.f, 1e-6f);
  CHECK_NEAR(t[2][1], 6.f, 1e-6f);
}

TEST_CASE("matrixN determinant matches known 3x3 value") {
  Matrix<f32, 3, 3> m{{6.f, 1.f, 1.f}, {4.f, -2.f, 5.f}, {2.f, 8.f, 7.f}};
  // Known determinant = -306
  CHECK_NEAR(m.determinant(), -306.f, 1e-2f);
}

TEST_CASE("matrixN determinant of identity is one for any size") {
  auto id4 = Matrix<f32, 4, 4>::identity();
  CHECK_NEAR(id4.determinant(), 1.f, 1e-4f);
  auto id5 = Matrix<f32, 5, 5>::identity();
  CHECK_NEAR(id5.determinant(), 1.f, 1e-4f);
}

TEST_CASE("matrixN trace only valid for square") {
  auto m = Matrix<f32, 3, 3>::identity();
  CHECK_NEAR(m.trace(), 3.f, 1e-6f);
}

TEST_CASE("matrixN addition and subtraction") {
  Matrix<f32, 2, 2> a{{1.f, 2.f}, {3.f, 4.f}};
  Matrix<f32, 2, 2> b{{5.f, 6.f}, {7.f, 8.f}};
  auto sum = a + b;
  auto diff = b - a;
  CHECK_NEAR(sum[0][0], 6.f, 1e-6f);
  CHECK_NEAR(diff[1][1], 4.f, 1e-6f);
}

TEST_CASE("matrixN scalar multiply and divide") {
  Matrix<f32, 2, 2> m{{2.f, 4.f}, {6.f, 8.f}};
  auto scaled = m * 0.5f;
  auto divided = m / 2.f;
  CHECK_NEAR(scaled[1][1], 4.f, 1e-6f);
  CHECK_NEAR(divided[1][1], 4.f, 1e-6f);
}

TEST_CASE("matrixN works with double") {
  Matrix<double, 2, 2> m{{1.0, 2.0}, {3.0, 4.0}};
  double det = m.determinant();
  CHECK_NEAR(static_cast<float>(det), -2.f, 1e-6f);
}

TEST_CASE("matrixN out of range row throws") {
  auto m = Matrix<f32, 3, 3>::identity();
  CHECK_THROWS(m[10]);
}
