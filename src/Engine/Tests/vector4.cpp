#include "Engine/Math/Vector4.h"
#include "Engine/core/Tester.h"
using namespace Engine::math;

TEST_CASE("Vector4 construction and indexing") {
  Vector4 v(1.f, 2.f, 3.f, 4.f);
  CHECK_NEAR(v[0], 1.f, 1e-6f);
  CHECK_NEAR(v[3], 4.f, 1e-6f);
}

TEST_CASE("Vector4 arithmetic") {
  Vector4 a(1.f, 2.f, 3.f, 4.f), b(4.f, 3.f, 2.f, 1.f);
  CHECK((a + b) == Vector4(5.f, 5.f, 5.f, 5.f));
  CHECK((a * 2.f) == Vector4(2.f, 4.f, 6.f, 8.f));
}

TEST_CASE("Vector4 equality and inequality") {
  Vector4 a(1.f, 2.f, 3.f, 4.f), b(1.f, 2.f, 3.f, 4.f), c(1.f, 2.f, 3.f, 99.f);
  CHECK(a == b);
  // KNOWN BUG: operator!= uses && instead of ||, mirrors the Vector3 bug.
  CHECK(a != c);
}

TEST_CASE("Vector4 scalar div friend uses w correctly") {
  // KNOWN BUG (previously): operator/(f32, Vector4) used u.z instead of u.w
  // for the w component. This test locks in the correct behavior.
  Vector4 v(2.f, 4.f, 5.f, 10.f);
  Vector4 r = 20.f / v;
  CHECK_NEAR(r.w, 2.f, 1e-5f); // 20/10, NOT 20/5
}

TEST_CASE("Vector4 round uses w correctly") {
  // KNOWN BUG (previously): round() used u.z twice instead of u.z then u.w.
  Vector4 v(1.2f, 1.7f, 2.5f, 3.9f);
  Vector4 r = round(v);
  CHECK_NEAR(r.w, 4.f, 1e-5f);
}

TEST_CASE("Vector4 magnitude and normalize") {
  Vector4 v(1.f, 2.f, 2.f, 0.f); // magnitude 3
  CHECK_NEAR(v.magnitude(), 3.f, 1e-5f);
  Vector4 n = v.normalized();
  CHECK(n.isNormalized());
}

TEST_CASE("Vector4 dot product") {
  Vector4 a(1.f, 2.f, 3.f, 4.f), b(4.f, 3.f, 2.f, 1.f);
  CHECK_NEAR(a.dot(b), 1 * 4 + 2 * 3 + 3 * 2 + 4 * 1, 1e-5f);
}

TEST_CASE("Vector4 xyz and xy swizzles") {
  Vector4 v(1.f, 2.f, 3.f, 4.f);
  Vector3 xyz = v.xyz();
  Vector2 xy = v.xy();
  CHECK_NEAR(xyz.x, 1.f, 1e-6f);
  CHECK_NEAR(xyz.z, 3.f, 1e-6f);
  CHECK_NEAR(xy.x, 1.f, 1e-6f);
  CHECK_NEAR(xy.y, 2.f, 1e-6f);
}

TEST_CASE("Vector4 lerp") {
  Vector4 a(0.f, 0.f, 0.f, 0.f), b(4.f, 4.f, 4.f, 4.f);
  Vector4 mid = a.lerp(b, 0.5f);
  CHECK_NEAR(mid.x, 2.f, 1e-5f);
}

TEST_CASE("Vector4 slerp does not mutate caller argument") {
  // KNOWN BUG (previously): slerp(v) took v by non-const ref and flipped
  // it in place when dot < 0, corrupting the caller's vector. This test
  // locks in that calling slerp leaves the input vectors untouched.
  Vector4 a(1.f, 0.f, 0.f, 0.f);
  Vector4 b(-1.f, 0.f, 0.001f, 0.f); // dot(a,b) < 0 forces the flip branch
  Vector4 bCopyBefore = b;
  a.slerp(b, 0.5f);
  CHECK_NEAR(b.x, bCopyBefore.x, 1e-6f);
  CHECK_NEAR(b.y, bCopyBefore.y, 1e-6f);
  CHECK_NEAR(b.z, bCopyBefore.z, 1e-6f);
  CHECK_NEAR(b.w, bCopyBefore.w, 1e-6f);
}

TEST_CASE("Vector4 reflect off a hyperplane") {
  Vector4 incoming(1.f, -1.f, 0.f, 0.f);
  Vector4 normal(0.f, 1.f, 0.f, 0.f);
  Vector4 reflected = incoming.reflect(normal);
  CHECK_NEAR(reflected.y, 1.f, 1e-5f);
}

TEST_CASE("Vector4 clampMagnitude") {
  Vector4 v(3.f, 4.f, 0.f, 0.f); // magnitude 5
  Vector4 clamped = v.clampMagnitude(2.f);
  CHECK_NEAR(clamped.magnitude(), 2.f, 1e-4f);
}

TEST_CASE("Vector4 min max abs hadamard") {
  Vector4 a(-1.f, 5.f, 2.f, 0.f), b(3.f, 1.f, 2.f, -1.f);
  CHECK(max(a, b) == Vector4(3.f, 5.f, 2.f, 0.f));
  CHECK(min(a, b) == Vector4(-1.f, 1.f, 2.f, -1.f));
  CHECK(abs(a) == Vector4(1.f, 5.f, 2.f, 0.f));
}
