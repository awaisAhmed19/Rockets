#include "Engine/Math/Vector3.h"
#include "Engine/Core/Tester.h"
using namespace Engine::math;

using namespace Engine;
TEST_CASE("Vector3 construction and indexing") {
  Vector3 v(1.f, 2.f, 3.f);
  CHECK_NEAR(v[0], 1.f, 1e-6f);
  CHECK_NEAR(v[1], 2.f, 1e-6f);
  CHECK_NEAR(v[2], 3.f, 1e-6f);
}

TEST_CASE("Vector3 arithmetic") {
  Vector3 a(1.f, 2.f, 3.f), b(4.f, 5.f, 6.f);
  CHECK((a + b) == Vector3(5.f, 7.f, 9.f));
  CHECK((b - a) == Vector3(3.f, 3.f, 3.f));
  CHECK((a * 2.f) == Vector3(2.f, 4.f, 6.f));
}

TEST_CASE("Vector3 equality and inequality") {
  Vector3 a(1.f, 2.f, 3.f), b(1.f, 2.f, 3.f), c(1.f, 2.f, 99.f);
  CHECK(a == b);
  // KNOWN BUG: operator!= uses && instead of ||, so vectors differing
  // in only one component are NOT reported as different. This test
  // documents the correct expected behavior and will fail until fixed.
  CHECK(a != c);
}

TEST_CASE("Vector3 dot and cross") {
  Vector3 x(1.f, 0.f, 0.f), y(0.f, 1.f, 0.f), z(0.f, 0.f, 1.f);
  CHECK_NEAR(x.dot(y), 0.f, 1e-6f);
  Vector3 cross = x.crossProduct(y);
  CHECK_NEAR(cross.x, z.x, 1e-6f);
  CHECK_NEAR(cross.y, z.y, 1e-6f);
  CHECK_NEAR(cross.z, z.z, 1e-6f);
}

TEST_CASE("Vector3 magnitude and normalize") {
  Vector3 v(2.f, 3.f, 6.f); // magnitude = 7
  CHECK_NEAR(v.magnitude(), 7.f, 1e-5f);
  Vector3 n = v.normalized();
  CHECK(n.isNormalized());
}

TEST_CASE("Vector3 rotateX rotateY rotateZ preserve magnitude") {
  Vector3 v(1.f, 2.f, 3.f);
  f32 mag = v.magnitude();
  CHECK_NEAR(v.rotateX(0.7f).magnitude(), mag, 1e-4f);
  CHECK_NEAR(v.rotateY(1.3f).magnitude(), mag, 1e-4f);
  CHECK_NEAR(v.rotateZ(2.1f).magnitude(), mag, 1e-4f);
}

TEST_CASE("Vector3 tripleProduct matches definition") {
  Vector3 a(1.f, 0.f, 0.f), b(0.f, 1.f, 0.f), c(0.f, 0.f, 1.f);
  Vector3 result = a.tripleProduct(b, c); // a x (b x c)
  Vector3 expected = a.crossProduct(b.crossProduct(c));
  CHECK_NEAR(result.x, expected.x, 1e-6f);
  CHECK_NEAR(result.y, expected.y, 1e-6f);
  CHECK_NEAR(result.z, expected.z, 1e-6f);
}

TEST_CASE("Vector3 reflect off a plane") {
  Vector3 incoming(1.f, -1.f, 0.f);
  Vector3 normal(0.f, 1.f, 0.f);
  Vector3 reflected = incoming.reflect(normal);
  CHECK_NEAR(reflected.y, 1.f, 1e-5f);
}

TEST_CASE("Vector3 refract total internal reflection returns zero vector") {
  // Grazing incidence (perpendicular to normal) with a large eta forces k < 0.
  Vector3 incoming(1.f, 0.f, 0.f);
  Vector3 normal(0.f, 1.f, 0.f);
  Vector3 r = incoming.refract(normal, 5.f);
  CHECK_NEAR(r.magnitude(), 0.f, 1e-5f);
}

TEST_CASE("Vector3 slerp endpoints match inputs") {
  Vector3 a(1.f, 0.f, 0.f), b(0.f, 1.f, 0.f);
  Vector3 s0 = a.slerp(b, 0.f);
  Vector3 s1 = a.slerp(b, 1.f);
  CHECK_NEAR(s0.x, a.x, 1e-3f);
  CHECK_NEAR(s1.y, b.y, 1e-3f);
}

TEST_CASE("Vector3 slerp midpoint stays on unit sphere for unit inputs") {
  Vector3 a(1.f, 0.f, 0.f), b(0.f, 1.f, 0.f);
  Vector3 mid = a.slerp(b, 0.5f);
  CHECK_NEAR(mid.magnitude(), 1.f, 1e-3f);
}

TEST_CASE("Vector3 clampMagnitude") {
  Vector3 v(3.f, 4.f, 0.f); // magnitude 5
  Vector3 clamped = v.clampMagnitude(2.f);
  CHECK_NEAR(clamped.magnitude(), 2.f, 1e-4f);
  Vector3 unclamped = v.clampMagnitude(10.f);
  CHECK_NEAR(unclamped.magnitude(), 5.f, 1e-4f);
}

TEST_CASE("Vector3 projection and rejection sum to original") {
  Vector3 a(3.f, 4.f, 5.f);
  Vector3 onto(1.f, 0.f, 0.f);
  Vector3 proj = a.vectorProjection(onto);
  Vector3 rej = a.rejectFrom(onto);
  CHECK_NEAR((proj + rej).x, a.x, 1e-4f);
  CHECK_NEAR((proj + rej).y, a.y, 1e-4f);
  CHECK_NEAR((proj + rej).z, a.z, 1e-4f);
}

TEST_CASE("Vector3 min max abs hadamard") {
  Vector3 a(-1.f, 5.f, 2.f), b(3.f, 1.f, 2.f);
  CHECK(max(a, b) == Vector3(3.f, 5.f, 2.f));
  CHECK(min(a, b) == Vector3(-1.f, 1.f, 2.f));
  CHECK(abs(a) == Vector3(1.f, 5.f, 2.f));
  CHECK(a.hadamardProduct(b) == Vector3(-3.f, 5.f, 4.f));
}
