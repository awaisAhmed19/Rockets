#include "Engine/Math/Matrix3.h"
#include "Engine/core/Tester.h"
using namespace Engine::math;

TEST_CASE("matrix3 identity multiply is identity") {
  Matrix3 id = Matrix3::identity();
  Vector3 v(1.f, 2.f, 3.f);
  Vector3 r = id * v;
  CHECK_NEAR(r.x, v.x, 1e-6f);
  CHECK_NEAR(r.y, v.y, 1e-6f);
  CHECK_NEAR(r.z, v.z, 1e-6f);
}

TEST_CASE("matrix3 column-vector constructor") {
  Vector3 c0(1.f, 4.f, 7.f), c1(2.f, 5.f, 8.f), c2(3.f, 6.f, 9.f);
  Matrix3 m(c0, c1, c2);
  CHECK_NEAR(m[0][0], 1.f, 1e-6f);
  CHECK_NEAR(m[0][1], 2.f, 1e-6f);
  CHECK_NEAR(m[0][2], 3.f, 1e-6f);
  CHECK_NEAR(m[2][2], 9.f, 1e-6f);
}

TEST_CASE("matrix3 multiply matches hand computation") {
  Matrix3 a = Matrix3::identity();
  Matrix3 b(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
  Matrix3 c = a * b;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      CHECK_NEAR(c[i][j], b[i][j], 1e-6f);
}

TEST_CASE("matrix3 determinant of identity is one") {
  CHECK_NEAR(Matrix3::identity().determinant(), 1.f, 1e-6f);
}

TEST_CASE("matrix3 determinant of singular matrix is zero") {
  Matrix3 singular(1.f, 2.f, 3.f, 2.f, 4.f, 6.f, 1.f, 1.f,
                   1.f); // row2 = 2*row1
  CHECK_NEAR(singular.determinant(), 0.f, 1e-4f);
}

TEST_CASE("matrix3 inverse composed with original is identity") {
  Matrix3 m(2.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f,
            4.f); // diagonal, easy to verify
  Matrix3 inv = m.inverse();
  Matrix3 result = m * inv;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      CHECK_NEAR(result[i][j], (i == j) ? 1.f : 0.f, 1e-4f);
}

// NOTE: RT_ASSERT calls std::abort() on failure (matching Assert::fail in
// the real project), it does not throw. So "inverse on a singular matrix"
// can't be exercised with CHECK_THROWS in this harness — that path is a
// hard process-terminating assert by design, not an exception.

TEST_CASE("matrix3 transpose swaps off-diagonal") {
  Matrix3 m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
  Matrix3 t = m.transposed();
  CHECK_NEAR(t[0][1], m[1][0], 1e-6f);
  CHECK_NEAR(t[1][2], m[2][1], 1e-6f);
}

TEST_CASE("matrix3 trace") {
  Matrix3 m = Matrix3::identity();
  CHECK_NEAR(m.trace(), 3.f, 1e-6f);
}

TEST_CASE("matrix3 rotation about Z preserves vector length") {
  // Build a rotation-like matrix manually and check length preservation
  f32 theta = 0.6f;
  Matrix3 rot(std::cos(theta), -std::sin(theta), 0.f, std::sin(theta),
              std::cos(theta), 0.f, 0.f, 0.f, 1.f);
  Vector3 v(1.f, 0.f, 0.f);
  Vector3 rotated = rot * v;
  CHECK_NEAR(rotated.magnitude(), v.magnitude(), 1e-4f);
}

TEST_CASE("matrix3 out of range row throws") {
  Matrix3 m = Matrix3::identity();
  CHECK_THROWS(m[10]);
}
