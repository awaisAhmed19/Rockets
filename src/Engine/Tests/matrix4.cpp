#include "Engine/Math/Matrix4.h"
#include "Engine/Core/Tester.h"
using namespace Engine::math;

using namespace Engine;
constexpr f32 kPi = 3.14159265358979323846f;

TEST_CASE("matrix4 identity multiply is identity") {
  Matrix4 id = Matrix4::identity();
  Vector4 v(1.f, 2.f, 3.f, 4.f);
  Vector4 r = id * v;
  CHECK_NEAR(r.x, v.x, 1e-6f);
  CHECK_NEAR(r.w, v.w, 1e-6f);
}

TEST_CASE("matrix4 translation moves points, not directions") {
  Matrix4 t = Matrix4::translation(Vector3(5.f, 0.f, 0.f));
  Vector3 point = t.transformPoint(Vector3(1.f, 1.f, 1.f));
  Vector3 dir = t.transformVector(Vector3(1.f, 1.f, 1.f));
  CHECK_NEAR(point.x, 6.f, 1e-5f); // translated
  CHECK_NEAR(dir.x, 1.f, 1e-5f);   // NOT translated (w=0)
}

TEST_CASE("matrix4 scale scales points and directions equally") {
  Matrix4 s = Matrix4::scale(Vector3(2.f, 3.f, 4.f));
  Vector3 point = s.transformPoint(Vector3(1.f, 1.f, 1.f));
  CHECK_NEAR(point.x, 2.f, 1e-5f);
  CHECK_NEAR(point.y, 3.f, 1e-5f);
  CHECK_NEAR(point.z, 4.f, 1e-5f);
}

TEST_CASE("matrix4 rotateZ by 90 degrees rotates X axis to Y axis") {
  Matrix4 r = Matrix4::rotateZ(kPi / 2.f);
  Vector3 result = r.transformVector(Vector3(1.f, 0.f, 0.f));
  CHECK_NEAR(result.x, 0.f, 1e-4f);
  CHECK_NEAR(result.y, 1.f, 1e-4f);
}

TEST_CASE("matrix4 rotateAxisAngle about Y matches rotateY") {
  f32 angle = 0.85f;
  Matrix4 r1 = Matrix4::rotateY(angle);
  Matrix4 r2 = Matrix4::rotateAxisAngle(Vector3(0.f, 1.f, 0.f), angle);
  Vector3 v(1.f, 0.5f, 0.25f);
  Vector3 a = r1.transformVector(v);
  Vector3 b = r2.transformVector(v);
  CHECK_NEAR(a.x, b.x, 1e-4f);
  CHECK_NEAR(a.y, b.y, 1e-4f);
  CHECK_NEAR(a.z, b.z, 1e-4f);
}

TEST_CASE(
    "matrix4 TRS composition applies scale, then rotate, then translation") {
  Matrix4 rot = Matrix4::rotateZ(kPi / 2.f);
  Matrix4 trs =
      Matrix4::trs(Vector3(10.f, 0.f, 0.f), rot, Vector3(2.f, 2.f, 2.f));
  Vector3 result = trs.transformPoint(Vector3(1.f, 0.f, 0.f));
  // scale: (2,0,0) -> rotateZ90: (0,2,0) -> translate: (10,2,0)
  CHECK_NEAR(result.x, 10.f, 1e-4f);
  CHECK_NEAR(result.y, 2.f, 1e-4f);
}

TEST_CASE("matrix4 lookAt places eye at local origin looking down -Z") {
  Vector3 eye(0.f, 0.f, 5.f);
  Vector3 target(0.f, 0.f, 0.f);
  Vector3 up(0.f, 1.f, 0.f);
  Matrix4 view = Matrix4::lookAt(eye, target, up);
  Vector3 eyeInViewSpace = view.transformPoint(eye);
  CHECK_NEAR(eyeInViewSpace.x, 0.f, 1e-4f);
  CHECK_NEAR(eyeInViewSpace.y, 0.f, 1e-4f);
  CHECK_NEAR(eyeInViewSpace.z, 0.f, 1e-4f);

  Vector3 targetInViewSpace = view.transformPoint(target);
  CHECK_NEAR(targetInViewSpace.x, 0.f, 1e-4f);
  CHECK_NEAR(targetInViewSpace.y, 0.f, 1e-4f);
  CHECK(targetInViewSpace.z < 0.f); // forward is -Z in view space
}

TEST_CASE("matrix4 perspective maps near plane center near z=-1 in NDC") {
  Matrix4 proj = Matrix4::perspective(kPi / 3.f, 16.f / 9.f, 0.1f, 100.f);
  Vector4 nearPoint(0.f, 0.f, -0.1f, 1.f);
  Vector4 clip = proj * nearPoint;
  f32 ndcZ = clip.z / clip.w;
  CHECK_NEAR(ndcZ, -1.f, 1e-3f);
}

TEST_CASE("matrix4 perspective maps far plane center to z=1 in NDC") {
  Matrix4 proj = Matrix4::perspective(kPi / 3.f, 16.f / 9.f, 0.1f, 100.f);
  Vector4 farPoint(0.f, 0.f, -100.f, 1.f);
  Vector4 clip = proj * farPoint;
  f32 ndcZ = clip.z / clip.w;
  CHECK_NEAR(ndcZ, 1.f, 1e-3f);
}

TEST_CASE("matrix4 orthographic maps box corners to NDC cube") {
  Matrix4 ortho = Matrix4::orthographic(-10.f, 10.f, -5.f, 5.f, 0.1f, 100.f);
  Vector3 corner = ortho.transformPoint(Vector3(10.f, 5.f, -100.f));
  CHECK_NEAR(corner.x, 1.f, 1e-3f);
  CHECK_NEAR(corner.y, 1.f, 1e-3f);
  CHECK_NEAR(corner.z, 1.f, 1e-3f);
}

TEST_CASE("matrix4 inverse composed with original is identity") {
  Matrix4 m = Matrix4::trs(Vector3(3.f, -2.f, 1.f), Matrix4::rotateY(0.4f),
                           Vector3(1.5f, 1.5f, 1.5f));
  Matrix4 inv = m.inversed();
  Matrix4 result = m * inv;
  Matrix4 id = Matrix4::identity();
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      CHECK_NEAR(result[i][j], id[i][j], 1e-3f);
}

TEST_CASE(
    "matrix4 rigidInverse matches general inverse for a TR-only transform") {
  Matrix4 m = Matrix4::trs(
      Vector3(3.f, -2.f, 1.f), Matrix4::rotateY(0.4f),
      Vector3(1.f, 1.f, 1.f)); // uniform scale = 1, safe for rigidInverse
  Matrix4 generalInv = m.inversed();
  Matrix4 rigidInv = m.rigidInverse();
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      CHECK_NEAR(generalInv[i][j], rigidInv[i][j], 1e-3f);
}

TEST_CASE("matrix4 determinant of identity is one") {
  CHECK_NEAR(Matrix4::identity().determinant(), 1.f, 1e-5f);
}

TEST_CASE("matrix4 determinant of scale matrix equals product of scales") {
  Matrix4 s = Matrix4::scale(Vector3(2.f, 3.f, 4.f));
  CHECK_NEAR(s.determinant(), 24.f, 1e-4f);
}

TEST_CASE("matrix4 transpose swaps off-diagonal") {
  Matrix4 m = Matrix4::translation(Vector3(1.f, 2.f, 3.f));
  Matrix4 t = m.transposed();
  CHECK_NEAR(t[3][0], m[0][3], 1e-6f);
  CHECK_NEAR(t[0][3], m[3][0], 1e-6f);
}

TEST_CASE("matrix4 embedding a Matrix3 leaves translation identity") {
  Matrix3 rot3 = Matrix3::identity();
  Matrix4 m(rot3);
  CHECK_NEAR(m[3][3], 1.f, 1e-6f);
  CHECK_NEAR(m[0][3], 0.f, 1e-6f);
}

TEST_CASE("matrix4 out of range row throws") {
  Matrix4 m = Matrix4::identity();
  CHECK_THROWS(m[4]);
}
