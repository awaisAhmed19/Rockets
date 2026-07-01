# Roadmap — Rockets Engine

Sprint-ordered ticket roadmap. Each ticket must satisfy the Definition of Done in `skill.md` before the next ticket in its milestone begins (vertical-slice rule). Ticket IDs follow `RE-###`, grouped by milestone.

Legend: **P0** blocking, **P1** required for MVP, **P2** stretch.

---

## Milestone 0 — Foundation

| ID | Ticket | Priority | Depends on |
|---|---|---|---|
| RE-001 | SDL window init/resize/shutdown | P0 | — |
| RE-002 | Renderer init, clear, present, background color | P0 | RE-001 |
| RE-003 | Fixed-timestep game loop + accumulator (`architecture.md` §4) | P0 | RE-002 |
| RE-004 | Delta time + FPS counter | P1 | RE-003 |
| RE-005 | Clean shutdown path (reverse-init-order teardown) | P0 | RE-003 |
| RE-006 | Logging (info/warn/error) | P1 | RE-001 |
| RE-007 | Assertions (debug-only, with expression + message capture) | P1 | RE-006 |
| RE-008 | Keyboard input | P0 | RE-001 |
| RE-009 | Mouse input (position + buttons) | P0 | RE-008 |
| RE-010 | Mouse wheel | P1 | RE-009 |
| RE-011 | Controller input | P2 | RE-008 |

---

## Milestone 1 — Mathematics

See `math_notes.md` for full derivations backing each ticket.

| ID | Ticket | Priority | Depends on |
|---|---|---|---|
| RE-012 | Vector2 (add, sub, scalar mul, dot, magnitude, normalize, distance) | P0 | — |
| RE-013 | Vector3 (Vector2 ops + cross product) | P0 | RE-012 |
| RE-014 | Matrix4 (identity, translation, rotation, scale) | P0 | RE-013 |
| RE-015 | Matrix4 multiplication (row-major vs column-major decision, `decisions/ADR-0001`) | P0 | RE-014 |
| RE-016 | Matrix4 inverse (general + fast affine-inverse path) | P0 | RE-015 |
| RE-017 | Matrix4 transpose | P1 | RE-014 |
| RE-018 | Quaternion construction (axis-angle, from-Euler, from-matrix) | P0 | RE-013 |
| RE-019 | Quaternion multiplication (Hamilton product) | P0 | RE-018 |
| RE-020 | Quaternion normalization + drift correction | P0 | RE-019 |
| RE-021 | Quaternion SLERP | P1 | RE-019 |
| RE-022 | Transform component (position, rotation, scale) | P0 | RE-018 |
| RE-023 | Local → world transform composition | P0 | RE-022, RE-015 |

---

## Milestone 2 — Camera

| ID | Ticket | Priority | Depends on |
|---|---|---|---|
| RE-024 | Free camera (WASD + mouse-look, pitch/yaw) | P0 | RE-023 |
| RE-025 | Orbit camera (target, distance, orbit, pan, zoom) | P0 | RE-024 |
| RE-026 | Perspective projection (FOV, aspect, near/far) | P0 | RE-014 |
| RE-027 | Orthographic projection | P1 | RE-014 |
| RE-028 | Coordinate space pipeline: Local→World→View→Clip→NDC→Screen | P0 | RE-023, RE-026 |
| RE-029 | Floating-origin camera rebasing (`rendering_notes.md` §3) | P1 | RE-025 |

---

## Milestone 3 — Rendering

| ID | Ticket | Priority | Depends on |
|---|---|---|---|
| RE-030 | Mesh representation | P0 | RE-002 |
| RE-031 | Vertex buffer | P0 | RE-030 |
| RE-032 | Index buffer | P0 | RE-030 |
| RE-033 | Texture loading | P1 | RE-002 |
| RE-034 | Material system | P1 | RE-033 |
| RE-035 | Shader compilation + uniform binding | P0 | RE-031 |
| RE-036 | Basic lighting (Lambert/Blinn-Phong) | P1 | RE-035 |
| RE-037 | Skybox | P2 | RE-035 |

---

## Milestone 4 — ECS

See `ecs_notes.md` for storage layout and scheduler design.

| ID | Ticket | Priority | Depends on |
|---|---|---|---|
| RE-038 | Entity id allocation (generational indices) | P0 | — |
| RE-039 | Component registration (compile-time type registry) | P0 | RE-038 |
| RE-040 | Archetype storage (SoA tables) | P0 | RE-039 |
| RE-041 | Entity creation/destruction (archetype migration) | P0 | RE-040 |
| RE-042 | Query system (component signature matching) | P0 | RE-040 |
| RE-043 | System scheduler (dependency graph, `architecture.md` §4.1) | P0 | RE-042 |

---

## Milestone 5 — Physics

See `physics_notes.md` for the full derivation chain (kinematics → dynamics → collision → resolution → constraints).

| ID | Ticket | Priority | Depends on |
|---|---|---|---|
| RE-044 | Kinematics: position/velocity/acceleration integration (semi-implicit Euler) | P0 | RE-043 |
| RE-045 | RK4 integrator option for high-eccentricity orbits | P1 | RE-044 |
| RE-046 | Dynamics: force accumulation, mass, `F = ma` | P0 | RE-044 |
| RE-047 | Impulse-based velocity resolution | P0 | RE-046 |
| RE-048 | Ray-based collision queries | P1 | RE-044 |
| RE-049 | Sphere-sphere collision | P0 | RE-046 |
| RE-050 | AABB-AABB collision (broadphase) | P0 | RE-046 |
| RE-051 | OBB-OBB collision (SAT, narrowphase) | P1 | RE-050 |
| RE-052 | Contact point + normal generation | P0 | RE-049, RE-051 |
| RE-053 | Restitution + friction (Coulomb model) | P1 | RE-052 |
| RE-054 | Spring constraint | P1 | RE-047 |
| RE-055 | Joint constraint (fixed + hinge, for staging/decoupling) | P0 | RE-047 |
| RE-056 | Gravity: two-body point-mass model (`physics_notes.md` §5) | P0 | RE-046 |
| RE-057 | Aerodynamic drag model (`physics_notes.md` §7) | P1 | RE-046 |
| RE-058 | Thrust + variable mass (Tsiolkovsky rocket equation, `physics_notes.md` §11) | P0 | RE-046 |

---

## Milestone 6 — Scene

| ID | Ticket | Priority | Depends on |
|---|---|---|---|
| RE-059 | Scene graph (parent/child hierarchy) | P0 | RE-023 |
| RE-060 | Parent-child transform propagation (dirty-flag based) | P0 | RE-059 |
| RE-061 | Scene loading (deserialization) | P1 | RE-059 |
| RE-062 | Scene saving (serialization) | P1 | RE-061 |

---

## Milestone 7 — Resources

| ID | Ticket | Priority | Depends on |
|---|---|---|---|
| RE-063 | Asset manager (handle-based, refcounted) | P0 | RE-006 |
| RE-064 | Texture cache | P1 | RE-063 |
| RE-065 | Mesh cache | P1 | RE-063 |
| RE-066 | Shader cache | P1 | RE-063 |
| RE-067 | Hot reload (filesystem watch) | P2 | RE-063 |

---

## Milestone 8 — Debug Tools

| ID | Ticket | Priority | Depends on |
|---|---|---|---|
| RE-068 | FPS/frame-time overlay | P1 | RE-004 |
| RE-069 | Memory usage overlay | P2 | RE-063 |
| RE-070 | Entity count overlay | P2 | RE-043 |
| RE-071 | Physics debug draw (contacts, AABBs, velocity vectors) | P1 | RE-052 |
| RE-072 | Camera debug draw (frustum, orbit target) | P2 | RE-028 |
| RE-073 | Orbit trajectory prediction overlay (conic section preview, `physics_notes.md` §12) | P2 | RE-056 |

---

## Milestone 9 — Game Layer (Rocket)

Not part of core engine, but tracked here since it is the vertical slice's payoff.

| ID | Ticket | Priority | Depends on |
|---|---|---|---|
| RE-074 | Part graph (attachment nodes, stack/radial) | P0 | RE-059 |
| RE-075 | Staging system (decouple = ECS entity graph edit + joint removal) | P0 | RE-055, RE-074 |
| RE-076 | Thruster component (thrust curve, gimbal, ISP) | P0 | RE-058 |
| RE-077 | Fuel tank component (mass flow, drain, center-of-mass shift) | P0 | RE-058 |
| RE-078 | Planet definition (μ, radius, atmosphere model) | P0 | RE-056, RE-057 |
| RE-079 | Flight computer: prograde/retrograde/normal hold (`physics_notes.md` §13) | P1 | RE-076 |

---

## Sequencing notes

- Milestones 0–1 must fully close before Milestone 2 opens (camera needs transforms).
- Milestone 4 (ECS) can be developed in parallel with Milestone 1–3 up to RE-043, but nothing in Milestone 5 may begin until RE-043 lands, since physics is scheduled through the ECS.
- Milestone 5 is the mathematically heaviest milestone and should not be rushed; see `physics_notes.md` for why semi-implicit Euler is insufficient for orbital tickets (RE-056) and RK4 (RE-045) is required before RE-078.
