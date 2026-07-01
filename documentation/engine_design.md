# Engine Design — Rockets Engine

Design details one layer below `architecture.md`: concrete subsystem interfaces and the reasoning behind them. Where `architecture.md` says *what* talks to *what*, this document says *how*.

---

## 1. Core loop implementation

```cpp
struct Clock {
    double accumulator = 0.0;
    static constexpr double kFixedDt = 1.0 / 120.0; // seconds; see physics_notes.md §6
};

void runFrame(Clock& clock, double frameDt) {
    // Clamp to avoid the "spiral of death" if a frame stalls (debugger, OS hitch).
    frameDt = std::min(frameDt, 0.25);
    clock.accumulator += frameDt;

    while (clock.accumulator >= Clock::kFixedDt) {
        fixedUpdate(Clock::kFixedDt);
        clock.accumulator -= Clock::kFixedDt;
    }

    double alpha = clock.accumulator / Clock::kFixedDt;
    renderInterpolated(alpha);
}
```

The `0.25s` clamp is a deliberate correctness/UX tradeoff: without it, a single long stall causes the accumulator to demand many catch-up fixed steps, which can itself cause a worse stall (spiral of death). Clamping sacrifices exact real-time correspondence during a stall in exchange for stability — acceptable because a simulation stall is already a degraded state.

## 2. Renderer interpolation

For every simulated `Transform`, the engine retains `prev` and `curr` values from the last two fixed steps:

```
interpolatedPosition = lerp(prev.position, curr.position, alpha)
interpolatedRotation  = slerp(prev.rotation, curr.rotation, alpha)   // see math_notes.md §4.5
```

Scale is linearly interpolated (rare for it to change per-frame, but supported for e.g. fairing deployment animations).

## 3. Subsystem interfaces

### 3.1 Math (`Engine/Math`)
Free-function + value-type library. No subsystem state — pure computation. See `math_notes.md`.

### 3.2 ECS (`Engine/ECS`)
```cpp
World world;
Entity e = world.create();
world.add<Transform>(e, {...});
world.add<RigidBodyState>(e, {...});

world.query<Transform, RigidBodyState>().forEach([](Entity e, Transform& t, RigidBodyState& rb) {
    // batched, cache-friendly iteration over the archetype table
});
```
See `ecs_notes.md` for archetype storage and scheduler details.

### 3.3 Physics (`Engine/Physics`)
Operates entirely through ECS queries — it has no private simulation state outside components. `PhysicsSystem::fixedUpdate(World&, double dt)` is the single entry point invoked by the scheduler.

Physics is decomposed into ordered sub-stages (see `physics_notes.md` for the math of each):

1. **Force accumulation** — gather thrust, gravity, drag, spring/joint reaction forces into a per-body net force/torque.
2. **Integration** — semi-implicit Euler (default) or RK4 (opt-in per body group, RE-045) advances velocity then position.
3. **Broadphase** — AABB sweep to find candidate collision pairs (RE-050).
4. **Narrowphase** — SAT/OBB or sphere tests to produce contact manifolds (RE-051/052).
5. **Resolution** — impulse-based solver resolves velocity, positional correction resolves penetration (RE-047/053).
6. **Constraints** — joints and springs solved as velocity constraints, iterative (Gauss-Seidel style), typically 4–8 iterations for a rocket's stack of joints (RE-054/055).

### 3.4 Renderer (`Engine/Renderer`)
Thin, explicit: `beginFrame() → submit(DrawCall) → endFrame()`. No scene knowledge — it consumes already-resolved world matrices and camera matrices; it does not walk the scene graph itself (that is `Scene`'s job, producing a flat draw list).

### 3.5 Scene (`Engine/Scene`)
Owns the parent/child hierarchy and produces:
- world transforms (`TransformSystem`, dirty-flag propagation — only recompute subtrees whose ancestor changed, an O(changed) rather than O(n) traversal),
- a flat, render-ready draw list handed to `Renderer`.

### 3.6 Assets (`Engine/Assets`)
Handle-based (`AssetHandle<T>`, an index + generation, same pattern as ECS entity ids — see `ecs_notes.md` §2 for the generational-index rationale, reused here for consistency). Reference counted; hot reload (RE-067) swaps underlying resource without invalidating handles held by gameplay code.

---

## 4. Why fixed-step + interpolation instead of variable-step

Three alternatives were considered (recorded formally in `decisions/ADR-0001-engine-architecture.md`):

1. **Variable timestep** (`dt = frameTime`) — simplest, but non-deterministic and numerically unstable for stiff constraints (a rocket's stack of joints under high thrust is a stiff system; large/irregular `dt` causes joint "explosion"). Rejected.
2. **Fixed step, no interpolation** — deterministic but visually stutters at any framerate that isn't an exact multiple of the physics rate. Rejected for a game that needs smooth rendering at arbitrary refresh rates.
3. **Fixed step + interpolation** (chosen) — deterministic simulation, smooth rendering, standard technique (Gaffer's "Fix Your Timestep"). Cost: one extra `prev`/`curr` transform pair per entity, negligible under DoD layout.

---

## 5. Floating origin

Orbital-scale worlds (low orbit ~6.6×10^6 m from a planet's center, up to interplanetary transfers) exceed single-precision float precision for render-space positions (`rendering_notes.md` §3, `physics_notes.md` §9). Engine design response:

- Simulation state (`Engine/Physics`) is always `double`, always in a fixed inertial frame centered on the *current dominant gravitational body* (see `physics_notes.md` §5.3 on sphere-of-influence patched conics) — never rebased.
- Only the **render-space** copy of position (float, relative to the active camera/vessel origin) is periodically rebased. This is a presentation-layer operation, entirely inside `Engine/Renderer` + `Engine/Scene`, invisible to `Engine/Physics`.

This keeps the physics/math layer simple (always double, always one consistent frame) and isolates the float-precision workaround to exactly the layer that needs it.

---

## 6. Cross-references

- `architecture.md` — module boundaries and the frame execution order this document implements.
- `ecs_notes.md` — archetype storage backing §3.2/3.3.
- `physics_notes.md` — derivations backing §3.3 stages.
- `rendering_notes.md` — floating-origin rendering mechanics backing §5.
- `decisions/ADR-0001-engine-architecture.md` — fixed-step decision record.
- `decisions/ADR-0002-renderer.md` — renderer API decision record.
- `decisions/ADR-0003-ecs.md` — ECS storage decision record.
