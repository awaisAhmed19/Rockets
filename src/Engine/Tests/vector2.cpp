#include "Engine/Math/Vector2.h"
#include "Engine/core/Tester.h"
using namespace Engine::math;

TEST_CASE("vector2 construction and indexing") {
  vector2 v(3.f, 4.f);
  CHECK_NEAR(v.x, 3.f, 1e-6f);
  CHECK_NEAR(v.y, 4.f, 1e-6f);
  CHECK_NEAR(v[0], 3.f, 1e-6f);
  CHECK_NEAR(v[1], 4.f, 1e-6f);
}

TEST_CASE("vector2 arithmetic") {
  vector2 a(1.f, 2.f), b(3.f, 4.f);
  CHECK((a + b) == vector2(4.f, 6.f));
  CHECK((b - a) == vector2(2.f, 2.f));
  CHECK((a * 2.f) == vector2(2.f, 4.f));
  CHECK((a / 2.f) == vector2(0.5f, 1.f));
  CHECK((-a) == vector2(-1.f, -2.f));
}

TEST_CASE("vector2 equality and inequality") {
  vector2 a(1.f, 2.f), b(1.f, 2.f), c(1.f, 3.f);
  CHECK(a == b);
  CHECK(a != c); // differs in only y
  CHECK(!(a != b));
}

TEST_CASE("vector2 magnitude and normalize") {
  vector2 v(3.f, 4.f);
  CHECK_NEAR(v.magnitude(), 5.f, 1e-5f);
  CHECK_NEAR(v.magnitudeSquared(), 25.f, 1e-5f);
  vector2 n = v.normalized();
  CHECK(n.isNormalized());
  CHECK_NEAR(n.magnitude(), 1.f, 1e-5f);
}

TEST_CASE("vector2 dot and cross") {
  vector2 a(1.f, 0.f), b(0.f, 1.f);
  CHECK_NEAR(a.dot(b), 0.f, 1e-6f);
  CHECK_NEAR(a.crossProduct(b), 1.f, 1e-6f);
}

TEST_CASE("vector2 lerp") {
  vector2 a(0.f, 0.f), b(10.f, 10.f);
  vector2 mid = a.lerp(b, 0.5f);
  CHECK_NEAR(mid.x, 5.f, 1e-5f);
  CHECK_NEAR(mid.y, 5.f, 1e-5f);
}

TEST_CASE("vector2 rotate 90 degrees") {
  vector2 v(1.f, 0.f);
  vector2 r = v.rotate(90.f);
  CHECK_NEAR(r.x, 0.f, 1e-4f);
  CHECK_NEAR(r.y, 1.f, 1e-4f);
}

TEST_CASE("vector2 rotate with fractional angle does not truncate") {
  vector2 v(1.f, 0.f);
  vector2 r1 = v.rotate(45.5f);
  vector2 r2 = v.rotate(45.f);
  // If rotate() truncated internally, these would be identical.
  CHECK(!(Tester::near(r1.x, r2.x, 1e-6f) && Tester::near(r1.y, r2.y, 1e-6f)));
}

TEST_CASE("vector2 rotateAround preserves distance to center") {
  vector2 center(1.f, 1.f);
  vector2 p(3.f, 1.f);
  vector2 rotated = p.rotateAround(center, 37.25f); // fractional angle
  CHECK_NEAR(rotated.distance(center), p.distance(center), 1e-3f);
}

TEST_CASE("vector2 perpendicular is orthogonal") {
  vector2 v(2.f, 5.f);
  vector2 p = v.perpendicular();
  CHECK_NEAR(v.dot(p), 0.f, 1e-5f);
}

TEST_CASE("vector2 reflect off flat surface") {
  vector2 incoming(1.f, -1.f);
  vector2 normal(0.f, 1.f);
  vector2 reflected = incoming.reflect(normal);
  CHECK_NEAR(reflected.x, 1.f, 1e-5f);
  CHECK_NEAR(reflected.y, 1.f, 1e-5f);
}

TEST_CASE("vector2 projection and rejection sum to original") {
  vector2 a(3.f, 4.f);
  vector2 onto(1.f, 0.f);
  vector2 proj = a.vectorProjection(onto);
  vector2 rej = a.rejectFrom(onto);
  CHECK_NEAR((proj + rej).x, a.x, 1e-4f);
  CHECK_NEAR((proj + rej).y, a.y, 1e-4f);
}

TEST_CASE("vector2 slerp endpoints") {
  vector2 a(1.f, 0.f), b(0.f, 1.f);
  vector2 s0 = a.slerp(b, 0.f);
  vector2 s1 = a.slerp(b, 1.f);
  CHECK_NEAR(s0.x, a.x, 1e-3f);
  CHECK_NEAR(s0.y, a.y, 1e-3f);
  CHECK_NEAR(s1.x, b.x, 1e-3f);
  CHECK_NEAR(s1.y, b.y, 1e-3f);
}

TEST_CASE("vector2 isZero and nearEqual") {
  vector2 z(0.f, 0.f);
  CHECK(z.isZero());
  vector2 a(1.0000001f, 2.f), b(1.f, 2.f);
  CHECK(a.nearEqual(b));
}

TEST_CASE("vector2 min max abs floor ceil round") {
  vector2 a(-1.5f, 3.7f), b(2.f, 1.f);
  CHECK(max(a, b) == vector2(2.f, 3.7f));
  CHECK(min(a, b) == vector2(-1.5f, 1.f));
  CHECK(abs(a) == vector2(1.5f, 3.7f));
  CHECK(floor(a) == vector2(-2.f, 3.f));
  CHECK(ceil(a) == vector2(-1.f, 4.f));
}
