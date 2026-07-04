# EPIC — Math Foundation

## MATH-001 — Scalar Math Library

**Priority:** Critical

### Description

Implement generic scalar math functions that form the foundation for vectors, matrices, interpolation, physics, animation, and rendering.

### Tasks

#### Basic Functions

* [ ] abs()
* [ ] sign()
* [ ] min()
* [ ] max()
* [ ] clamp()
* [ ] saturate()

#### Interpolation

* [ ] lerp()
* [ ] inverseLerp()
* [ ] remap()

#### Curves

* [ ] smoothstep()
* [ ] smootherstep()
* [ ] cubic interpolation

#### Trigonometry

* [ ] radians()
* [ ] degrees()

#### Floating Point

* [ ] epsilonEqual()
* [ ] isZero()
* [ ] isFinite()
* [ ] isNaN()

#### Utility

* [ ] nextPowerOfTwo()
* [ ] align()
* [ ] wrap()
* [ ] pingPong()

### DoD

* 100% unit tested
* constexpr where possible
* templated for float/double
* documented

---

# EPIC — Vector Mathematics

---

# MATH-100 — Vec2

### Construction

* [x] default constructor
* [x] scalar constructor
* [x] component constructor

### Operators

* [x] +
* [x] -
* [x] *
* [x] /
* [x] +=
* [x] -=
* [x] *=
* [x] /=

### Access

* [ ] operator[]
* [ ] data()

### Properties

* [x] magnitude()
* [x] magnitudeSquared()
* [x] normalize()
* [ ] normalized()
* [x] distance()
* [ ] distanceSquared()

### Products

* [x] dot()
* [ ] cross (2D scalar cross)

### Advanced

* [ ] angle()
* [ ] angleBetween()
* [ ] project()
* [ ] reject()
* [ ] reflect()
* [ ] refract()

### Utility

* [ ] clamp()
* [ ] min()
* [ ] max()
* [ ] floor()
* [ ] ceil()
* [ ] round()
* [ ] abs()

### Constants

* [ ] Zero
* [ ] One
* [ ] Up
* [ ] Down
* [ ] Left
* [ ] Right

---

# MATH-101 — Vec3

Exactly the same checklist, plus

### Cross Product

* [x] cross()

### Rotations

* [ ] rotateAroundAxis()
* [ ] rotateByQuaternion()

### Constants

* [ ] Forward
* [ ] Back
* [ ] Up
* [ ] Down
* [ ] Left
* [ ] Right

---

# MATH-102 — Vec4

Same as Vec3

Additional

* [ ] xyz()
* [ ] homogenize()

---

# EPIC — Matrix Mathematics

---

# MATH-200 — Matrix3

### Construction

* [x] identity
* [ ] zero
* [ ] copy

### Operators

* [ ] multiply
* [ ] scalar multiply
* [ ] transpose

### Math

* [ ] determinant
* [ ] inverse

### Transformations

* [ ] rotation
* [ ] scale

---

# MATH-201 — Matrix4

### Construction

* [ ] identity
* [ ] zero

### Operators

* [ ] multiplication
* [ ] transpose
* [ ] inverse

### Transformations

* [ ] translation
* [ ] scale
* [ ] rotationX
* [ ] rotationY
* [ ] rotationZ
* [ ] rotationAxisAngle

### Camera

* [ ] lookAt()

### Projection

* [ ] perspective()
* [ ] orthographic()

### Transform

* [ ] transformPoint()
* [ ] transformVector()
* [ ] transformNormal()

### Decomposition

* [ ] TRS compose
* [ ] TRS decompose

---

# EPIC — Quaternion

---

# MATH-300 — Quaternion

### Construction

* [ ] identity
* [ ] axis-angle
* [ ] Euler
* [ ] matrix conversion

### Operations

* [ ] normalize
* [ ] inverse
* [ ] conjugate
* [ ] multiply

### Interpolation

* [ ] nlerp
* [ ] slerp
* [ ] squad (future)

### Rotation

* [ ] rotate vector
* [ ] rotate matrix

---

# EPIC — Geometry

---

# MATH-400 — Primitive Types

### Lines

* [ ] Line
* [ ] Segment
* [ ] Ray

### Planes

* [ ] Plane

### Volumes

* [ ] Sphere
* [ ] Capsule
* [ ] Cylinder
* [ ] Cone

### Boxes

* [ ] AABB
* [ ] OBB

### Camera

* [ ] Frustum

### Mesh

* [ ] Triangle

---

# EPIC — Geometry Algorithms

---

# MATH-500 — Distance Queries

* [ ] Point → Plane
* [ ] Point → Line
* [ ] Point → Segment
* [ ] Point → Triangle
* [ ] Point → AABB

---

# MATH-501 — Closest Point Queries

* [ ] Closest point on line
* [ ] Closest point on segment
* [ ] Closest point on plane
* [ ] Closest point on triangle
* [ ] Closest point on AABB

---

# MATH-502 — Ray Casting

* [ ] Ray → Plane
* [ ] Ray → Triangle
* [ ] Ray → Sphere
* [ ] Ray → Capsule
* [ ] Ray → AABB
* [ ] Ray → OBB

---

# MATH-503 — Intersection Tests

* [ ] Sphere ↔ Sphere
* [ ] Sphere ↔ AABB
* [ ] AABB ↔ AABB
* [ ] OBB ↔ OBB (SAT)
* [ ] Frustum ↔ Sphere
* [ ] Frustum ↔ AABB

---

# MATH-504 — Barycentric Coordinates

* [ ] Compute barycentric
* [ ] Triangle interpolation

---

# MATH-505 — Convex Geometry

* [ ] Convex Hull (2D)
* [ ] GJK support functions (future)
* [ ] EPA support (future)

---

# EPIC — Noise

---

# MATH-600 — Random Number Generator

### Scalars

* [ ] randomInt()
* [ ] randomFloat()
* [ ] randomBool()

### Vectors

* [ ] insideSphere()
* [ ] onSphere()
* [ ] insideCircle()

### Utility

* [ ] randomDirection()

---

# MATH-601 — Perlin Noise

* [ ] 1D
* [ ] 2D
* [ ] 3D
* [ ] Tiling support

---

# MATH-602 — Simplex Noise

* [ ] 2D
* [ ] 3D

---

# MATH-603 — Fractal Noise

* [ ] FBM
* [ ] Turbulence
* [ ] Ridged Noise

---

### EPIC — Transform Mathematics

* **MATH-700 — Transform Class**

  * Position
  * Rotation (Quaternion)
  * Scale
  * Local Matrix
  * World Matrix
  * Dirty Flag
  * Parent Transform
  * Child Transform
  * TRS Composition
  * TRS Decomposition
  * Local ↔ World Space Conversion

