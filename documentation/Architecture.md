# Architecture — Rockets Engine

## 1. Purpose

This document defines the system architecture of Rockets Engine: module boundaries, data flow, ownership rules, and the execution model that every subsystem must conform to. 
It is the contract between "Engine" and "Game" referenced in `skill.md`.

If a change alters a module boundary, an ownership rule, or the execution model, this document must be updated in the same commit 
(see `skill.md` → Definition of Done → Documentation).

---

## 2. Layering

```
┌─────────────────────────────────────────────┐
│                    Game                      │
│  Rocket/  Planet/  FuelTank/  Thruster/      │
│  (knows about the engine, not vice versa)    │
└───────────────────▲───────────────────────────┘
                     │ uses
┌───────────────────┴───────────────────────────┐
│                   Engine                       │
│  Renderer/ Math/ Physics/ Assets/ ECS/ Scene/  │
│  (knows nothing about rockets)                 │
└─────────────────────────────────────────────────┘
```

**Rule:** dependency arrows point one direction only, Game → Engine. Engine headers must never `#include` anything under `Game/`. This is enforced structurally (separate include roots) and reviewed per Definition of Done.

### 2.1 Why this separation matters mathematically

Because Engine has no knowledge of rockets, it also has no knowledge of *thrust*, *fuel mass depletion*, or *staging*. Those are just:

- a time-varying force vector `F(t)` applied at a local attachment point,
- a time-varying scalar mass `m(t)`,
- and discrete topology changes (an entity graph edit) at staging events.

The Physics module only needs to support **applying forces/torques at arbitrary body-local offsets** and **mutating mass properties over time**. 
Everything rocket-specific is composed on top of these generic primitives in `Game/Rocket`.

---

## 3. Module responsibilities

| Module | Owns | Does NOT own |
|---|---|---|
| `Engine/Math` | Vector2/3, Matrix4, Quaternion, Transform, numeric utilities | any simulation state |
| `Engine/Physics` | rigid body state, integrators, collision, constraints | rendering, input |
| `Engine/ECS` | entity ids, component storage, archetypes, queries, scheduler | component *semantics* |
| `Engine/Renderer` | GPU resources, draw submission, camera matrices consumption | camera *control logic* |
| `Engine/Scene` | transform hierarchy, parent/child resolution, serialization | gameplay rules |
| `Engine/Assets` | loading, caching, hot reload | asset *authoring* |
| `Game/Rocket` | part graph, staging, thrust curves, aerodynamic coefficients | rendering internals |
| `Game/Planet` | gravitational body definition (μ, radius, atmosphere model) | physics integrator internals |

---

## 4. Execution model (per frame)

Rockets Engine uses a **fixed timestep simulation loop with rendering interpolation**, because orbital and rigid-body integration must be deterministic and frame-rate independent (see `physics_notes.md` §1).

```
accumulator += frameDeltaTime

while (accumulator >= FIXED_DT):
    FixedUpdate(FIXED_DT)     # Input → Physics → Transform → Constraints
    accumulator -= FIXED_DT

alpha = accumulator / FIXED_DT
RenderState = lerp(PrevState, CurrState, alpha)   # interpolated transforms only
Render(RenderState)
```

- `FIXED_DT` is a compile-time/config constant (typical: 1/120 s for rigid body stability with stiff rocket engines/joints; see `physics_notes.md` §6 on stiffness and stability).
- Interpolation (`alpha`) is applied **only** to transforms consumed by the renderer. Simulation state itself is never interpolated — it is exact at each fixed step.
- Determinism requirement: given the same input sequence and the same `FIXED_DT`, two runs must produce bit-reproducible (or numerically-equivalent within tolerance) trajectories. This is required for replay/debugging tools (Milestone 8) and for any future networking.

### 4.1 System ordering (ECS scheduler)

```
InputSystem
   ↓
GameLogicSystem      (Game/Rocket: staging events, control input → gimbal angles, throttle)
   ↓
PhysicsSystem        (integrate forces → velocities → positions, in FIXED_DT substeps)
   ↓
ConstraintSystem      (joints, fuel-flow constraints, contact resolution)
   ↓
TransformSystem       (local → world transform propagation through Scene graph)
   ↓
CameraSystem
   ↓
RenderSystem
```

Ordering is a hard dependency graph, not a suggestion: `TransformSystem` reads the *post-integration* positions, `CameraSystem` reads *post-transform* world matrices, `RenderSystem` reads *post-camera* view/projection matrices. Violating this order is a Definition-of-Done failure (see `ecs_notes.md` §4 for the scheduler's dependency declaration mechanism).

---

## 5. Data-oriented layout

Every simulated entity that participates in physics has its per-frame numeric state stored in **Structure-of-Arrays** form inside the ECS archetype tables, not in an OOP `RigidBody` class with virtual methods. See `dod.md` for the layout rationale and `ecs_notes.md` for how archetypes map to this.

Concretely, a rocket with N parts is **not** a tree of C++ objects each owning a `Transform`. It is:

- N entities,
- each with a `LocalTransform`, `WorldTransform`, `Mass`, `RigidBodyState` component row,
- iterated in tight batches by `PhysicsSystem`.

The *topology* (which part is attached to which, staging order) lives in a separate sparse graph structure (`Game/Rocket::PartGraph`), not in the per-frame hot data.

---

## 6. Coordinate spaces and units

See `math_notes.md` §5 for the full derivation. Summary:

- Engine-internal simulation uses **SI units**: meters, kilograms, seconds, radians.
- Rendering uses a **render-scale** transform applied only at the render boundary, because orbital-scale distances (10^6–10^8 m) lose float precision in a GPU-friendly single-precision pipeline. This is the **floating origin** problem — see `rendering_notes.md` §3 and `physics_notes.md` §9.
- All rotations are represented as unit quaternions internally; Euler angles are a UI-only presentation format (`math_notes.md` §4).

---

## 7. Determinism boundary

| Deterministic (fixed-step, SI, double where needed) | Non-deterministic / presentation-only |
|---|---|
| Physics integration | Camera interpolation |
| Staging logic | Particle VFX |
| Collision resolution | Audio |
| Fuel consumption | UI animation easing |

---

## 8. Cross-references

- Ticket roadmap: `roadmap.md`
- Coding conventions for all modules: `coding_style.md`
- Data-oriented rationale: `dod.md`
- ECS mechanics: `ecs_notes.md`
- Math derivations backing this doc: `math_notes.md`
- Physics derivations backing this doc: `physics_notes.md`
- Architectural decisions: `decisions/ADR-0001-engine-architecture.md`
