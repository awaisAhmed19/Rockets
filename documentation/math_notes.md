# Math Notes — Rockets Engine

Derivations backing Milestone 1 (`roadmap.md` RE-012–RE-023). Conventions here are binding — `coding_style.md` §4 requires code to match this document exactly.

**Conventions used throughout:** right-handed coordinate system, Y-up, column vectors, column-major matrices, `M_world = M_parent · M_local` (left multiplication of column vectors: `v' = M v`).

---

## 0. Notation

- Vectors: lowercase bold, `**v**`. Components `v = (vx, vy, vz)`.
- Matrices: uppercase, `M`. `M_ij` = row i, column j.
- Quaternion: `q = w + x**i** + y**j** + z**k**`, equivalently `q = (w, **v**)` with scalar `w` and vector part `**v** = (x,y,z)`.
- `·` dot product, `×` cross product, `⊗` quaternion (Hamilton) product.

---

## 1. Vector2 / Vector3 (RE-012, RE-013)

### 1.1 Basic operations

For `**a** = (ax, ay, az)`, `**b** = (bx, by, bz)`:

- Addition: `**a** + **b** = (ax+bx, ay+by, az+bz)`
- Scalar multiplication: `s**a** = (s·ax, s·ay, s·az)`
- Dot product: `**a**·**b** = ax·bx + ay·by + az·bz = |**a**||**b**|cos θ`
- Magnitude: `|**a**| = √(**a**·**a**)`
- Normalize: `â = **a** / |**a**|` (guard `|**a**| ≈ 0` → return zero vector, log, per `coding_style.md` §6)
- Distance: `d(**a**,**b**) = |**a** − **b**|`

### 1.2 Cross product (Vector3 only)

```
**a** × **b** = ( ay·bz − az·by,
                  az·bx − ax·bz,
                  ax·by − ay·bx )
```

Geometric meaning: `**a** × **b**` is perpendicular to both, with magnitude `|**a**||**b**|sin θ` (area of the parallelogram spanned by `**a**,**b**`), direction given by the right-hand rule (consistent with our right-handed convention — verify orientation with unit test per `coding_style.md` §4).

**Engine uses:** surface normals (`(**b**−**a**) × (**c**−**a**)` for a triangle), torque (`**τ** = **r** × **F**`, `physics_notes.md` §10), angular momentum (`**L** = **r** × **p**`), and constructing orthonormal bases (e.g. camera right/up vectors, RE-024).

### 1.3 Dot product identities used elsewhere

- Angle between vectors: `θ = acos( (**a**·**b**) / (|**a**||**b**|) )` — used for cone-of-visibility checks, gimbal limit clamping.
- Projection of `**a**` onto `**b**`: `proj_b(**a**) = ( (**a**·**b**) / (**b**·**b**) ) **b**`.
- Work/energy: `W = **F**·**d**`.

---

## 2. Matrix4 (RE-014–RE-017)

Column-major 4×4, homogeneous coordinates (`w=1` for points, `w=0` for directions).

### 2.1 Identity

```
I = | 1 0 0 0 |
    | 0 1 0 0 |
    | 0 0 1 0 |
    | 0 0 0 1 |
```

### 2.2 Translation

```
T(**t**) = | 1 0 0 tx |
           | 0 1 0 ty |
           | 0 0 1 tz |
           | 0 0 0 1  |
```
`T(**t**) · **p** = **p** + **t**` for a homogeneous point (w=1); for a direction (w=0) translation has no effect, which is exactly why the w-component distinguishes points from directions.

### 2.3 Rotation

Given axis-angle form is derived from Rodrigues' rotation formula. For unit axis `**n**=(nx,ny,nz)` and angle `θ`:

```
R = I + sin θ · [n]_× + (1 − cos θ) · [n]_×²
```
where `[n]_×` is the cross-product (skew-symmetric) matrix:
```
[n]_× = |  0   −nz   ny |
        |  nz   0   −nx |
        | −ny   nx   0  |
```
Note `[n]_× **v** = **n** × **v**` by construction — this is how the "cross product as a matrix" trick works and how rotation code derives directly from §1.2.

In practice the engine constructs rotation matrices from a quaternion (§4.2) rather than directly from axis-angle, since quaternions are the storage format (`coding_style.md` §4). Axis-angle is kept for authoring/derivation purposes and for RE-018's axis-angle constructor.

Elementary rotations about X/Y/Z (used for intermediate math and for the Euler→quaternion conversion in §4.4):

```
Rx(θ) = | 1    0       0     0 |      Ry(θ) = |  cosθ  0  sinθ  0 |
        | 0  cosθ  −sinθ    0 |               |   0    1   0    0 |
        | 0  sinθ   cosθ    0 |               | −sinθ  0  cosθ  0 |
        | 0    0       0     1 |               |   0    0   0    1 |

Rz(θ) = | cosθ  −sinθ  0  0 |
        | sinθ   cosθ  0  0 |
        |  0      0    1  0 |
        |  0      0    0  1 |
```

Handedness check: rotating `(1,0,0)` by `Rz(90°)` should yield `(0,1,0)` — counter-clockwise about +Z viewed from +Z looking toward origin, consistent with right-handed convention (`coding_style.md` §4).

### 2.4 Scale

```
S(**s**) = | sx  0   0   0 |
           |  0  sy  0   0 |
           |  0   0  sz  0 |
           |  0   0  0   1 |
```

### 2.5 Composite TRS

```
M = T(**t**) · R(q) · S(**s**)
```
Order matters: this applies scale first, then rotation, then translation to a point — the standard convention, matching `Transform` composition in §5.

### 2.6 Multiplication

Standard matrix product, `(AB)_ij = Σ_k A_ik B_kj`. Non-commutative: `AB ≠ BA` in general — this is *why* TRS order in §2.5 is a meaningful design decision, not arbitrary.

### 2.7 Inverse

General 4×4 inverse (cofactor expansion / adjugate, or Gauss-Jordan) is O(n³)-ish and expensive; the engine special-cases the common **affine inverse** (rotation + translation + uniform/non-uniform scale, no shear/projection):

For `M = T(**t**)·R·S` with `R` orthonormal (`R⁻¹ = Rᵀ`):

```
M⁻¹ = S⁻¹ · Rᵀ · T(−**t**)
```
where `S⁻¹ = S(1/sx, 1/sy, 1/sz)`. This avoids general Gaussian elimination for the overwhelmingly common case (every `Transform` in the scene graph), falling back to general inverse only for true projection matrices (used once per camera per frame, not per-entity).

### 2.8 Transpose

`(Mᵀ)_ij = M_ji`. Used for: normal-vector transforms (a normal must be transformed by the **inverse-transpose** of the model matrix to remain perpendicular to the surface under non-uniform scale — standard result, derived from requiring `**n**'·**t**' = 0` is preserved when tangent `**t**` transforms by `M`), and for `R⁻¹ = Rᵀ` in §2.7.

---

## 3. Coordinate spaces (RE-028)

```
Local → World → View → Clip → NDC → Screen
```

- **Local → World:** `p_world = M_world · p_local`, where `M_world` is the accumulated parent chain from the scene graph (`engine_design.md` §3.5).
- **World → View:** `p_view = V · p_world`, `V = M_camera⁻¹` (the view matrix is the inverse of the camera's own world transform — a camera "looks through" the inverse of where it sits).
- **View → Clip:** `p_clip = P · p_view`, `P` is the projection matrix (§ below).
- **Clip → NDC:** perspective divide, `p_ndc = (p_clip.x, p_clip.y, p_clip.z) / p_clip.w`. This is where perspective foreshortening actually happens — `w` after projection equals `−z_view` for a standard perspective matrix, so dividing by it makes farther objects shrink.
- **NDC → Screen:** viewport transform, `screen_x = (ndc_x·0.5+0.5)·width`, `screen_y = (1 − (ndc_y·0.5+0.5))·height` (Y flip because screen space is typically top-left origin).

### 3.1 Perspective projection matrix (RE-026)

For vertical FOV `fovY`, aspect ratio `a = width/height`, near `n`, far `f`:

```
f_ = 1 / tan(fovY/2)

P = | f_/a   0        0             0           |
    |  0     f_       0             0           |
    |  0     0    (f+n)/(n−f)   (2fn)/(n−f)      |
    |  0     0       −1             0            |
```
This maps `z_view ∈ [−n, −f]` (camera looks down −Z in view space) to `z_ndc ∈ [−1, 1]` and sets `w_clip = −z_view` so the perspective divide (§3) produces correct foreshortening.

### 3.2 Orthographic projection (RE-027)

For box `[l,r]×[b,t]×[n,f]`:
```
P = | 2/(r−l)    0         0        −(r+l)/(r−l) |
    |   0      2/(t−b)     0        −(t+b)/(t−b) |
    |   0        0      −2/(f−n)    −(f+n)/(f−n) |
    |   0        0         0              1       |
```
No division by `w` needed (`w=1` throughout) — this is precisely why orthographic projection has no foreshortening.

---

## 4. Quaternion (RE-018–RE-021)

### 4.1 Why quaternions instead of Euler angles or matrices for rotation state

- **Gimbal lock:** Euler angle composition (e.g. Z-Y-X) can align two rotation axes, losing a degree of freedom. A rocket in an arbitrary orientation (e.g. pitched 90°) will hit this. Quaternions have no such singularity.
- **Interpolation:** SLERP (§4.5) between two quaternions gives a constant-angular-velocity rotation path; interpolating Euler angles component-wise does not correspond to any consistent physical rotation.
- **Compactness/renormalization:** 4 numbers vs 9 for a matrix, and renormalizing a drifted quaternion (§4.3) is cheaper and more numerically robust than re-orthonormalizing a matrix.

### 4.2 Construction

**From axis-angle** (unit axis `**n**`, angle `θ`):
```
q = ( cos(θ/2), sin(θ/2)·**n** )   →   w = cos(θ/2), (x,y,z) = sin(θ/2)·**n**
```

**From quaternion to rotation matrix** (used once per entity per frame at most, cached until rotation changes):
```
R = | 1−2(y²+z²)   2(xy−wz)     2(xz+wy)   |
    | 2(xy+wz)     1−2(x²+z²)   2(yz−wx)   |
    | 2(xz−wy)     2(yz+wx)     1−2(x²+y²) |
```

### 4.3 Multiplication (Hamilton product) and normalization

For `q1=(w1,**v1**)`, `q2=(w2,**v2**)`:
```
q1 ⊗ q2 = ( w1w2 − **v1**·**v2**,   w1**v2** + w2**v1** + **v1**×**v2** )
```
Composing rotations: applying `q1` then `q2` to a vector corresponds to `q2 ⊗ q1` (right-to-left composition — verify against §2.6 matrix convention with a unit test, since a sign/order mismatch here is a classic bug).

**Normalization:** repeated multiplication (e.g. integrating angular velocity every physics step, `physics_notes.md` §10.3) accumulates floating point drift so `|q| ≠ 1`. Renormalize:
```
q_normalized = q / |q|,   |q| = √(w²+x²+y²+z²)
```
Engine rule (`coding_style.md` §4): renormalize every physics step after quaternion integration — cheap (one rsqrt), and the alternative (drift compounding over thousands of steps) silently corrupts orientation.

### 4.4 Euler ↔ quaternion (UI boundary only)

Conversion exists solely for human-readable input/output (`coding_style.md` §2). For Z-Y-X (yaw-pitch-roll) convention:
```
q = qz(yaw) ⊗ qy(pitch) ⊗ qx(roll)
```
where each `qx/qy/qz(θ)` is the axis-angle construction (§4.2) about the respective elementary axis. This conversion is only ever applied at the moment of reading a UI field or displaying one — never stored as simulation state (§4.1).

### 4.5 SLERP

Spherical linear interpolation between unit quaternions `q0, q1` at parameter `t ∈ [0,1]`:
```
cos Ω = q0 · q1     (quaternion dot product = w0w1+x0x1+y0y1+z0z1)

if cos Ω < 0: negate q1 and cos Ω  (take the shorter arc)

if cos Ω > 1−ε:  lerp + renormalize   (nearly parallel — avoid divide-by-~0 in sin Ω)
else:
    Ω = acos(cos Ω)
    slerp(q0,q1,t) = [ sin((1−t)Ω)/sinΩ ] q0 + [ sin(tΩ)/sinΩ ] q1
```
Used for render interpolation (`engine_design.md` §2) and for smoothing camera/vessel orientation transitions.

---

## 5. Transform & units (RE-022, RE-023)

### 5.1 Transform component

```
struct Transform {
    Vector3    position;   // meters, double, world/parent-relative per architecture.md §6
    Quaternion rotation;   // unit quaternion
    Vector3    scale;      // dimensionless, default (1,1,1)
};
```

### 5.2 Local → world composition

```
M_local  = T(position) · R(rotation) · S(scale)     (§2.5)
M_world  = M_parent_world · M_local
```
computed bottom-up via the scene graph traversal in `engine_design.md` §3.5. Note: non-uniform scale composed through a hierarchy can introduce shear in child transforms — a known limitation accepted for MVP (documented so it isn't "discovered" later as a bug); rocket part hierarchies use uniform scale in practice, avoiding the issue.

### 5.3 Units

SI throughout the simulation layer: meters (m), kilograms (kg), seconds (s), radians (rad), Newtons (N = kg·m/s²), Newton-meters (N·m) for torque. See `architecture.md` §6 and `physics_notes.md` §0 for the full unit table and the float/double boundary rule.

---

## 6. Numerical utilities

- `nearlyEqual(a, b, ε)`: `|a−b| ≤ ε · max(1, |a|, |b|)` (relative+absolute hybrid, robust across magnitude scales from part-level to orbital-level quantities).
- `clamp(x, lo, hi)`, `lerp(a,b,t) = a + t(b−a)`, `saturate(x) = clamp(x,0,1)`.
- `wrapAngle(θ)`: reduces to `(−π, π]`, needed anywhere a raw angle accumulates over many orbits (e.g. true anomaly) and must not silently overflow precision.

---

## 7. Cross-references

- `physics_notes.md` — where these primitives get consumed (forces, torques, integration).
- `rendering_notes.md` — where the coordinate-space pipeline (§3) is realized on the GPU.
- `coding_style.md` §4 — binding conventions this document must match.
- `decisions/ADR-0001-engine-architecture.md` — column-major/row-major and left/right-handed decision record.
