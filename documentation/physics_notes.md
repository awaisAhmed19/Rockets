# Physics Notes — Rockets Engine

Derivations backing Milestone 5 (`roadmap.md` RE-044–RE-058) and Milestone 9 rocket-specific systems. This is the mathematically central document of the engine — a SimpleRockets-style game lives or dies on this subsystem's correctness.

---

## 0. Units and constants

SI throughout (`math_notes.md` §5.3, `architecture.md` §6). Constants live in `Physics/Constants.hpp` (`coding_style.md` §5), sourced from here:

| Symbol | Meaning | Value |
|---|---|---|
| `G` | Newtonian gravitational constant | 6.674×10⁻¹¹ m³ kg⁻¹ s⁻² |
| `g0` | standard gravity (for ISP↔exhaust-velocity conversion) | 9.80665 m/s² |
| `μ = GM` | standard gravitational parameter (per-planet, precomputed) | planet-specific |

---

## 1. Kinematics & integration (RE-044, RE-045)

### 1.1 Continuous equations of motion

```
d**x**/dt = **v**
d**v**/dt = **a** = **F**_net / m
```

These are exact; the engine's job is numerically integrating them stably and efficiently.

### 1.2 Semi-implicit (symplectic) Euler — default integrator

```
**v**_{n+1} = **v**_n + **a**_n · dt
**x**_{n+1} = **x**_n + **v**_{n+1} · dt      ← uses the NEW velocity
```

This differs from explicit Euler (`x_{n+1} = x_n + v_n·dt`) only in *which* velocity updates position — but that one change matters enormously: semi-implicit Euler is **symplectic**, meaning it approximately conserves the system's Hamiltonian (energy) over long integration, whereas explicit Euler systematically injects energy and orbits/oscillators visibly diverge (spiral outward) over time. This is why semi-implicit, not explicit, Euler is the default (RE-044).

Error per step: O(dt²) local, O(dt) global — same order as explicit Euler, but the symplectic property makes the *qualitative* long-term behavior far better for oscillatory/orbital systems, which is what matters for a game that runs for many simulated minutes.

### 1.3 RK4 — for high-eccentricity orbits (RE-045)

For `dy/dt = f(t,y)`:
```
k1 = f(t, y)
k2 = f(t + dt/2, y + dt/2·k1)
k3 = f(t + dt/2, y + dt/2·k2)
k4 = f(t + dt,   y + dt·k3)
y_{n+1} = y_n + dt/6·(k1 + 2k2 + 2k3 + k4)
```
Local error O(dt⁵), global O(dt⁴) — much higher accuracy per step than Euler, at 4× the force evaluations. Used opt-in for bodies where semi-implicit Euler's constant-`dt` sampling under-resolves rapidly-changing acceleration — specifically near periapsis of a high-eccentricity orbit, where `**a** ∝ 1/r²` (§5) spikes. Symptom without RK4: energy drift causes periapsis altitude to creep up or down over many orbits ("orbital decay/growth" artifacts that shouldn't exist for an unperturbed two-body orbit).

### 1.4 Timestep selection (`engine_design.md` §1)

`FIXED_DT = 1/120 s` chosen as a balance: small enough for stiff joint stacks (§14) to remain stable, large enough to keep the physics substep count per rendered frame reasonable (2 substeps at 60 fps rendering).

---

## 2. Dynamics (RE-046)

### 2.1 Newton's second law

```
**F**_net = Σ **F**_i = m **a**   ⟹   **a** = **F**_net / m
```
For rotation, the analogous law (§10) uses torque and the inertia tensor instead of force and scalar mass.

### 2.2 Force accumulation

Each fixed step (`engine_design.md` §3.3 stage 1), every rigid body sums:
```
**F**_net = **F**_gravity + **F**_thrust + **F**_drag + **F**_constraint-reaction + ...
**τ**_net = **τ**_thrust-offset + **τ**_aero + **τ**_constraint-reaction + ...
```
Each contributor is documented in its own section below (§5 gravity, §7 drag, §11 thrust, §14 constraints).

---

## 3. Mass properties

### 3.1 Center of mass

For a composite body (a whole rocket assembled from parts, each with mass `m_i` at local position `**r**_i`):
```
**r**_cm = (Σ m_i **r**_i) / (Σ m_i)
```
Recomputed whenever mass distribution changes — critically, **every physics step** for any part with draining fuel (RE-077), since fuel mass depletion continuously shifts `**r**_cm`. A rocket with asymmetric tank drain will visibly (and correctly) develop a torque as thrust no longer passes through the (moving) center of mass.

### 3.2 Inertia tensor

For a rigid body, the inertia tensor about its center of mass:
```
I = | Ixx  −Ixy  −Ixz |
    | −Ixy  Iyy  −Iyz |
    | −Ixz −Iyz  Izz  |

Ixx = Σ m_i (y_i² + z_i²)
Iyy = Σ m_i (x_i² + z_i²)
Izz = Σ m_i (x_i² + y_i²)
Ixy = Σ m_i x_i y_i    (similarly Ixz, Iyz)
```
For composite rockets, per-part inertia tensors are combined using the **parallel axis theorem**: for a part with its own inertia tensor `I_part` about its own COM, offset `**d**` from the composite COM,
```
I_contribution = I_part + m_part ( |**d**|² · Id − **d**⊗**d** )
```
where `Id` is the 3×3 identity and `**d**⊗**d**` is the outer product matrix. This is how a rocket's overall rotational inertia is built from simple analytic shapes (cylinders for tanks/stages, spheres for tanks, etc.) per part, without needing a full mesh-based inertia integral for MVP.

---

## 4. Impulse-based velocity resolution (RE-047)

An **impulse** `**J** = ∫**F** dt` produces an instantaneous velocity change `Δ**v** = **J**/m`, used for resolving collisions and constraints in a single velocity update rather than integrating a very large force over a very short time (which fixed-step integration cannot resolve accurately).

For a collision along contact normal `**n**` between bodies A, B with relative velocity `**v**_rel = **v**_A − **v**_B`, restitution `e`:
```
j = −(1+e) (**v**_rel·**n**) / (1/m_A + 1/m_B)
**v**_A += (j/m_A) **n**
**v**_B −= (j/m_B) **n**
```
Extended with angular terms (§10) for contact points off the center of mass — full form deferred to `physics_notes.md` §8.3.

---

## 5. Gravity — two-body model (RE-056, RE-078)

### 5.1 Newton's law of gravitation

```
**F** = −G (m1 m2 / r²) r̂
```
For simulation, since the rocket's mass is negligible compared to a planet, per-unit-mass acceleration is what matters:
```
**a** = −(μ/r²) r̂ ,     μ = GM_planet
```
`r̂` points from the vessel toward the planet center; the minus sign makes the acceleration attractive.

### 5.2 Orbital mechanics essentials

For a two-body Keplerian orbit with specific orbital energy `ε` and specific angular momentum `**h** = **r**×**v**`:
```
ε = v²/2 − μ/r = −μ/(2a)                (a = semi-major axis)
h = |**r**×**v**|
e = √(1 + 2εh²/μ²)                       (eccentricity)
```
Orbit shape from energy: `ε<0` ellipse (bound orbit), `ε=0` parabolic escape, `ε>0` hyperbolic escape — directly relevant to the flight computer / trajectory prediction overlay (RE-073).

**Kepler's third law** (circular-orbit sanity check used in unit tests per `coding_style.md` §8):
```
T = 2π √(a³/μ)
```

### 5.3 Sphere of influence (patched conics)

For multi-body scenes (rocket near a planet that itself orbits a star), full N-body gravity is unnecessary for MVP; the engine uses **patched conics**: the vessel is influenced by exactly one dominant body at a time, switching when it crosses that body's sphere of influence,
```
r_SOI ≈ a_planet (m_planet / m_star)^(2/5)
```
This is why `architecture.md` §4.1 describes gravity as acting in "the current dominant gravitational body's" frame — it is a deliberate simplification, documented so it is not mistaken for an oversight. True N-body gravity (`**a** = Σ_i −G m_i (**r**−**r**_i)/|**r**−**r**_i|³`) is a documented P2 stretch, not MVP.

---

## 6. Stability and stiffness

A "stiff" system is one where forces change on a much shorter timescale than the simulation's `dt` can resolve without instability — e.g. a tightly-coupled joint stack under high thrust trying to instantaneously enforce a rigid connection. Symptoms of `dt` too large for the stiffness present: joints visibly stretch, oscillate, or explode.

Mitigations used by this engine:
- Fixed `dt = 1/120s` (§1.4), smaller than naive per-frame `dt` would be.
- Iterative constraint solving (§14) rather than a single direct solve — trades exactness for stability, standard in real-time engines (Baumgarte stabilization / sequential impulses, same family of technique as Box2D/Bullet).
- Warm-starting solver iterations is a documented P2 optimization once profiling shows the constraint solver as a bottleneck.

---

## 7. Aerodynamic drag (RE-057)

### 7.1 Drag equation

```
**F**_drag = −½ ρ v² Cd A · v̂
```
where `ρ` = local atmospheric density (function of altitude, §7.2), `v` = airspeed relative to the atmosphere (accounting for planetary rotation if modeled), `Cd` = drag coefficient (part-specific, authored data), `A` = reference cross-sectional area, `v̂` = unit velocity direction (drag opposes relative motion — the minus sign and the `v̂` direction are what make it always decelerate, never accelerate).

### 7.2 Atmospheric density model

MVP uses an **exponential atmosphere** (standard simplification, adequate for a game, not aerospace-certified accuracy):
```
ρ(h) = ρ0 · exp(−h / H)
```
`ρ0` = sea-level density, `H` = scale height (planet-specific constants, `Game/Planet`), `h` = altitude above the planet's surface. This is simple enough to evaluate per-part per-step with negligible cost, and produces the qualitatively correct behavior (rapid density falloff, effectively zero above ~100km for Kerbin-like scale planets) that a SimpleRockets-style game needs.

### 7.3 Aerodynamic torque

Drag applied at a part's center of pressure, offset from the vessel's center of mass, produces torque exactly as in §10.1 — this is the physical origin of aerodynamic stability/instability (why fins at the tail stabilize a rocket: center of pressure behind center of mass means drag torque opposes any angular deviation from the velocity vector — restoring torque).

---

## 8. Collision detection (RE-048–RE-052)

### 8.1 Ray

Ray `**P**(t) = **o** + t**d**`. Ray-sphere intersection (sphere center `**c**`, radius `r`): substitute and solve the quadratic
```
t² (**d**·**d**) + 2t **d**·(**o**−**c**) + (**o**−**c**)·(**o**−**c**) − r² = 0
```
via the quadratic formula; real, non-negative roots are hits, smallest root is the nearest.

### 8.2 Sphere-sphere

Bodies with centers `**c1**,**c2**`, radii `r1,r2` collide iff `|**c1**−**c2**| < r1+r2`. Contact normal `**n** = (**c2**−**c1**)/|**c2**−**c1**|`, penetration depth `= r1+r2 − |**c1**−**c2**|`.

### 8.3 AABB-AABB (broadphase, RE-050)

Two axis-aligned boxes `[min1,max1], [min2,max2]` overlap iff they overlap on all three axes independently:
```
overlap = (min1.x ≤ max2.x && max1.x ≥ min2.x) && (same for y) && (same for z)
```
Used as a cheap broadphase filter before the more expensive narrowphase (§8.4) — O(1) per pair, applied after a spatial partition (see `dod.md` for the broadphase's own data layout) reduces candidate pairs from O(n²).

### 8.4 OBB-OBB via Separating Axis Theorem (RE-051)

Two convex shapes are **not** colliding iff there exists at least one axis onto which their projections don't overlap. For OBBs, it suffices to test 15 candidate axes: the 3 face normals of box A, the 3 face normals of box B, and the 9 cross products of each edge-axis pair (`a_i × b_j` for i,j ∈ {0,1,2}):
```
for each candidate axis L:
    project both boxes' extents onto L
    if projections don't overlap: SEPARATED, no collision, STOP (early-out)
if no separating axis found among all 15: COLLIDING
```
The minimum-overlap axis among all tested (when no separation is found) gives the contact normal and penetration depth for resolution (§4).

---

## 9. Floating point precision at scale

Single-precision `float` has ~7 significant decimal digits. At orbital altitude (`r ~ 10^7 m`), a float can only represent position to roughly ±1 meter precision, and this gets worse further out — unacceptable for a physics simulation where relative velocities and small forces must remain accurate over many steps. This is the concrete numeric justification for `coding_style.md` §2's double-for-physics rule and `engine_design.md` §5's floating-origin renderer design: physics state stays `double` and frame-invariant; only the transient render-space copy near the camera is ever narrowed to `float`, and even then only after being made small (camera-relative) by the floating-origin rebase.

---

## 10. Rotational dynamics (backs RE-047 angular terms, RE-055 joints)

### 10.1 Torque

```
**τ** = **r** × **F**
```
`**r**` is the vector from center of mass to the point of force application. This is precisely why thrust misalignment (nozzle gimbal, or an asymmetric engine cluster) produces rotation: any `**F**` not passing through the COM has nonzero `**r**×**F**`.

### 10.2 Euler's rotation equation

Analogous to `**F**=m**a**`, for angular motion in the body frame (where the inertia tensor is constant):
```
I dω/dt + ω × (Iω) = **τ**
```
The `ω×(Iω)` term is the gyroscopic coupling term — nonzero whenever `I` is not a multiple of identity (non-spherically-symmetric body, i.e. basically every rocket), meaning rotation about one axis can induce apparent torque affecting other axes. This term is what makes tumbling asymmetric bodies (like a tall thin rocket) behave differently than a sphere — physically real, not a bug, and must be included for correct rocket tumble/spin behavior.

### 10.3 Quaternion integration

Given angular velocity `**ω**` (world or body frame, consistently applied), the quaternion derivative is:
```
dq/dt = ½ · (0,**ω**) ⊗ q
```
(treating `**ω**` as a pure quaternion with zero scalar part). Semi-implicit integration:
```
q_{n+1} = q_n + dt · ½(0,**ω**)⊗q_n
q_{n+1} = normalize(q_{n+1})     ← required; see math_notes.md §4.3
```

---

## 11. Rocket propulsion (RE-058, RE-076, RE-077)

### 11.1 Tsiolkovsky rocket equation

The foundational equation of rocketry — derived from conservation of momentum for a system continuously ejecting mass:
```
Δv = v_e · ln(m0 / mf)
```
`v_e` = effective exhaust velocity, `m0` = initial (wet) mass, `mf` = final (dry) mass after propellant is spent. This gives the *total* achievable velocity change for a given engine/fuel combination — the single most important equation for rocket design gameplay (staging decisions, delta-v budgeting, RE-073's trajectory planning).

### 11.2 Specific impulse (ISP) and exhaust velocity

Engines are typically specified by ISP (seconds) rather than raw exhaust velocity, because ISP is thrust-independent of local gravity convention:
```
v_e = ISP · g0
```
(`g0` = standard gravity, §0 — used here purely as a *unit conversion constant*, not as the actual local gravity, which is why it's "standard" 9.80665 regardless of which planet the vessel is near — a common point of confusion worth documenting explicitly).

### 11.3 Thrust and mass flow rate

```
F_thrust = ṁ · v_e
```
`ṁ` = propellant mass flow rate (kg/s, engine-specific authored data or derived from rated thrust and ISP: `ṁ = F_thrust / v_e`). Each fixed step:
```
m(t+dt) = m(t) − ṁ · dt          (guard: clamp to 0 when tank empties, cut thrust)
```
This mass loss directly feeds back into: `**a** = **F**_net/m` (§2.1 — the same thrust force produces increasing acceleration as the vehicle gets lighter, correctly reproducing the "rocket accelerates faster as it burns fuel" behavior), the center-of-mass recompute (§3.1), and the inertia tensor recompute (§3.2).

### 11.4 Thrust vector and gimbal

```
**F**_thrust = F_thrust · R_gimbal(θ_pitch, θ_yaw) · n̂_nozzle
```
applied at the engine's local attachment point, contributing both `**F**_net` and (via `**r**×**F**`, §10.1) `**τ**_net` whenever the gimballed direction or the engine's offset from COM introduces a non-central force line — this is the physical mechanism behind thrust-vector-control steering (RE-079).

---

## 12. Trajectory prediction (RE-073)

For an unperturbed two-body segment (no thrust, no drag — i.e. coasting in vacuum), the future path is exactly the conic section defined by current `**r**, **v**` (§5.2) — no need to numerically step the preview forward; it can be computed analytically from the current orbital elements (`a, e`, and the orbital plane from `**h**=**r**×**v**`) and rendered as a static ellipse/hyperbola. Only when thrust or atmospheric drag is active does the preview fall back to numerical propagation (RK4, §1.3, run ahead in a scratch buffer, not affecting real simulation state).

---

## 13. Flight computer control laws (RE-079)

Prograde/retrograde/normal hold reduce to: compute a target orientation quaternion aligning the vessel's forward axis with a target direction vector, then drive gimbal/RCS torque to close the error.

```
v̂ = normalize(velocity)                       (prograde direction)
target_forward = v̂   (or −v̂ for retrograde, or normalize(**h**) for normal)

q_error = q_target ⊗ conjugate(q_current)      (rotation needed to align)
```
`q_error`'s axis-angle form (extract via `2·acos(w_error)` for angle, `(x,y,z)/sin(angle/2)` for axis — inverse of `math_notes.md` §4.2) gives a torque direction and magnitude for a PD controller:
```
**τ**_command = Kp · θ_error · axis_error − Kd · **ω**_current
```
standard proportional-derivative control on orientation error, damped by current angular velocity — prevents overshoot/oscillation.

---

## 14. Constraints (RE-054, RE-055)

### 14.1 Spring

```
**F**_spring = −k(x − x_rest) · x̂ − c · **v**_rel
```
Hooke's law term plus a damping term (`c`) — undamped springs in a discrete-time simulation tend to oscillate indefinitely or amplify numerical error; damping is not optional for stability at game timesteps.

### 14.2 Fixed/hinge joint (staging)

A fixed joint between two parts enforces `**r**_A + offset_A = **r**_B + offset_B` (positions of the shared attachment point must match) as a velocity constraint, solved iteratively (§6) alongside collision constraints each step. **Staging** (RE-075) is precisely the runtime removal of this constraint plus the corresponding ECS entity-graph edit (`architecture.md` §5, `Game/Rocket::PartGraph` in `architecture.md` §3) — physically, the two bodies simply stop being constrained together and evolve independently from that step onward, no special-case physics needed beyond "the constraint no longer exists."

---

## 15. Cross-references

- `math_notes.md` — vector/matrix/quaternion primitives used throughout.
- `architecture.md` §4, §7 — execution order and determinism requirements these derivations must respect.
- `ecs_notes.md` — how per-body physics state is stored/iterated.
- `dod.md` — why broadphase/narrowphase data is laid out as it is.
- `roadmap.md` — ticket IDs referenced throughout.
