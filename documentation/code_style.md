# Coding Style — Rockets Engine

C++20. This document defines conventions specific to a math/physics-heavy DoD engine — general style (braces, naming) is secondary to the numerical and data-layout rules below, which exist to prevent silent correctness bugs in simulation code.

---

## 1. Naming

| Kind | Convention | Example |
|---|---|---|
| Types (class/struct/enum) | `PascalCase` | `RigidBodyState`, `Quaternion` |
| Functions/methods | `camelCase` | `computeInverseInertiaTensor()` |
| Member variables | `m_camelCase` | `m_angularVelocity` |
| Free functions in `Math::` | `camelCase` | `Math::cross(a, b)` |
| Constants | `kPascalCase` | `kGravitationalConstant` |
| Template parameters | `PascalCase` | `template <typename ComponentT>` |
| Files | match primary type | `Quaternion.hpp` / `Quaternion.cpp` |

## 2. Numeric types — non-negotiable rules

Rocket simulation spans scales from millimeter part tolerances to interplanetary distances (10^0 to 10^11 m). Type discipline is a correctness requirement, not style preference.

- **`float`** — GPU-facing data only (vertex attributes, render-space transforms after floating-origin rebase). Never used for physics integration.
- **`double`** — all physics state: positions, velocities, accumulated time, orbital elements. See `physics_notes.md` §9 for why single precision silently breaks orbital mechanics at scale.
- Never compare floating point with `==`. Use `Math::nearlyEqual(a, b, epsilon)`.
- Angles are stored in **radians** in all engine/physics code. Degrees exist only at the UI input/output boundary, converted immediately via `Math::toRadians` / `Math::toDegrees`.
- Rotations are stored as `Quaternion`, never as Euler angles, anywhere state persists across a frame. Euler is a transient UI representation only (see `math_notes.md` §4.4 for gimbal lock rationale).

## 3. Data-Oriented Design rules

See `dod.md` for full rationale. Enforced rules:

- No inheritance hierarchies for simulated objects. A "rigid body" is a set of components (`Transform`, `RigidBodyState`, `Mass`, ...), not a class `RigidBody : public Entity`.
- No `virtual` in any type stored in an ECS archetype table. Virtual dispatch breaks contiguous layout assumptions and is a Definition-of-Done failure for hot-path types.
- Components are POD-like: trivially copyable, no owning pointers, no `std::function`. If a component needs indirection, it stores a handle/index into a resource table, not a raw or smart pointer.
- Hot-path loops iterate arrays directly (`for (size_t i = 0; i < count; ++i)`), not through iterator adapters that defeat autovectorization, unless profiling shows no regression.

## 4. Math library conventions

These must match `math_notes.md` exactly — a mismatch between code and derivation is a bug.

- **Matrices are column-major**, matching the convention used throughout `math_notes.md` and matching GPU upload layout (no transpose needed at the render boundary). See `decisions/ADR-0001-engine-architecture.md` for the tradeoff record.
- **Vectors are column vectors**; transforms compose as `M_world = M_parent * M_local` (left-multiply), never the reverse.
- **Quaternions are Hamilton convention**, `q = w + xi + yj + zk`, right-handed, and always kept unit-length after any operation that can introduce drift (renormalize after N multiplications — see `math_notes.md` §4.3).
- **Coordinate system is right-handed**, Y-up for the engine's internal convention (documented explicitly because SimpleRockets-style games sometimes use Z-up; this is a deliberate, singular decision — do not mix).
- Cross product sign, rotation direction (counter-clockwise about the axis when viewed from the positive end), and handedness must be verified against `math_notes.md` §2.3 by a unit test before merging any new geometric primitive.

## 5. Physics/simulation code rules

- All integrators are pure functions of `(state, forces, dt) → newState` where possible — no hidden global state — to preserve the determinism requirement in `architecture.md` §7.
- Any function that accumulates floating point error across many timesteps (e.g. quaternion integration, energy in a constraint solver) must have an accompanying test that measures drift over a fixed number of steps and asserts it stays below a documented tolerance.
- Constants (G, standard gravity, atmospheric constants) live in one place: `Physics/Constants.hpp`, sourced from `physics_notes.md` §0, never re-declared or magic-numbered inline.

## 6. Error handling

- `Engine/` code never throws exceptions in hot paths (allocation-heavy machinery uses assertions + error codes/`std::expected`).
- Invalid input (per Definition of Done: "Handles invalid input") is handled at API boundaries with explicit validation, not left to propagate as NaN. Any function that can produce NaN/Inf from bad input must guard and log via `Engine/Log`.
- Assertions (`RE_ASSERT`) are for programmer errors (invariant violations); they compile out in release. Validation is for data/user errors; it never compiles out.

## 7. Comments and documentation

- Public API functions get a doc comment stating: purpose, units of every parameter, units of return value, and any preconditions (e.g. "quaternion must be normalized").
- Any non-obvious formula in code must cite the exact section of `math_notes.md` or `physics_notes.md` it implements, e.g.:
  ```cpp
  // Semi-implicit Euler position update. See physics_notes.md §1.2.
  velocity += acceleration * dt;
  position += velocity * dt;
  ```
- No commented-out code in merged commits.

## 8. Testing

- Every Math/Physics ticket requires unit tests covering: identity cases, degenerate cases (zero vectors, singular matrices), and a known analytic solution where one exists (e.g. circular orbit period vs Kepler's third law, `physics_notes.md` §12.4).
- Numerical tests use tolerance-based assertions (`Math::nearlyEqual`), never exact equality, except for integer/index math.

## 9. File/module structure

Mirrors `architecture.md` §2–3 exactly. A new `.hpp`/`.cpp` pair under `Engine/` must not include any `Game/` header — this is checked by the build (separate include roots) and by code review.
