#include "Engine/Math/Matrix2.h"
#include "Engine/core/Tester.h"
using namespace Engine::math;

TEST_CASE("matrix2 identity multiply is identity") {
  Matrix2 id = Matrix2::identity();
  vector2 v(3.f, 4.f);
  vector2 r = id * v;
  CHECK_NEAR(r.x, v.x, 1e-6f);
  CHECK_NEAR(r.y, v.y, 1e-6f);
}

TEST_CASE("matrix2 column-vector constructor matches Matrix3 convention") {
  // c0, c1 are COLUMNS: [c0.x c1.x; c0.y c1.y]
  vector2 c0(1.f, 3.f), c1(2.f, 4.f);
  Matrix2 m(c0, c1);
  CHECK_NEAR(m[0][0], 1.f, 1e-6f);
  CHECK_NEAR(m[0][1], 2.f, 1e-6f);
  CHECK_NEAR(m[1][0], 3.f, 1e-6f);
  CHECK_NEAR(m[1][1], 4.f, 1e-6f);
}

TEST_CASE("matrix2 multiply matches hand computation") {
  Matrix2 a(1.f, 2.f, 3.f, 4.f);
  Matrix2 b(5.f, 6.f, 7.f, 8.f);
  Matrix2 c = a * b;
  // [1 2][5 6]   [1*5+2*7  1*6+2*8]   [19 22]
  // [3 4][7 8] = [3*5+4*7  3*6+4*8] = [43 50]
  CHECK_NEAR(c[0][0], 19.f, 1e-5f);
  CHECK_NEAR(c[0][1], 22.f, 1e-5f);
  CHECK_NEAR(c[1][0], 43.f, 1e-5f);
  CHECK_NEAR(c[1][1], 50.f, 1e-5f);
}

TEST_CASE("matrix2 determinant") {
  Matrix2 m(1.f, 2.f, 3.f, 4.f);
  CHECK_NEAR(m.determinant(), 1.f * 4.f - 2.f * 3.f, 1e-5f);
}

TEST_CASE("matrix2 inverse composed with original is identity") {
  Matrix2 m(4.f, 7.f, 2.f, 6.f);
  Matrix2 inv = m.inverse();
  Matrix2 shouldBeIdentity = m * inv;
  CHECK_NEAR(shouldBeIdentity[0][0], 1.f, 1e-3f);
  CHECK_NEAR(shouldBeIdentity[0][1], 0.f, 1e-3f);
  CHECK_NEAR(shouldBeIdentity[1][0], 0.f, 1e-3f);
  CHECK_NEAR(shouldBeIdentity[1][1], 1.f, 1e-3f);
}

TEST_CASE("matrix2 transpose") {
  Matrix2 m(1.f, 2.f, 3.f, 4.f);
  Matrix2 t = m.transposed();
  CHECK_NEAR(t[0][1], m[1][0], 1e-6f);
  CHECK_NEAR(t[1][0], m[0][1], 1e-6f);
}

TEST_CASE("matrix2 trace") {
  Matrix2 m(1.f, 2.f, 3.f, 4.f);
  CHECK_NEAR(m.trace(), 5.f, 1e-6f);
}

TEST_CASE("matrix2 scalar multiply and divide") {
  Matrix2 m(1.f, 2.f, 3.f, 4.f);
  Matrix2 scaled = m * 2.f;
  Matrix2 divided = scaled / 2.f;
  CHECK_NEAR(scaled[1][1], 8.f, 1e-6f);
  CHECK_NEAR(divided[1][1], 4.f, 1e-6f);
}

TEST_CASE("matrix2 out of range row throws") {
  Matrix2 m = Matrix2::identity();
  CHECK_THROWS(m[5]);
  const Matrix2 &cm = m;
  CHECK_THROWS(cm[-1]);
}
