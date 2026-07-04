
```text
Math
    ↓
RigidBody
    ↓
Force Integration
    ↓
Collision Detection
    ↓
Contact Generation
    ↓
Constraint Solver
    ↓
Physics World
```


---

# EPIC — Physics World

---

# PHYS-001 — Physics World

**Priority:** Critical

### Description

Implement the central simulation world responsible for managing all rigid bodies, constraints, collision detection, and physics updates.

### Responsibilities

* Physics timestep
* Gravity
* Rigid body storage
* Collision pipeline
* Constraint solving

### API

```cpp
PhysicsWorld world;

world.Initialize();

world.Step(dt);

world.Shutdown();
```

### Tasks

* [ ] Create world
* [ ] Destroy world
* [ ] Fixed timestep
* [ ] Gravity
* [ ] Add/remove rigid bodies
* [ ] Add/remove colliders
* [ ] Physics update loop

### Acceptance Criteria

* [ ] Fixed update
* [ ] Deterministic simulation
* [ ] Configurable gravity

---

# EPIC — Rigid Bodies

---

# PHYS-100 — RigidBody Component

### Description

Represent a simulated rigid body.

### Data

* Position
* Rotation
* Velocity
* Angular Velocity
* Mass
* Inverse Mass
* Inertia Tensor
* Inverse Inertia Tensor

### Body Types

* [ ] Static
* [ ] Dynamic
* [ ] Kinematic

### Acceptance Criteria

* [ ] Three body types
* [ ] Transform synchronization
* [ ] Sleep state

---

# PHYS-101 — Force Accumulator

### Description

Collect forces applied during a frame.

### API

```cpp
body.AddForce();

body.AddTorque();

body.ClearForces();
```

### Tasks

* [ ] Linear forces
* [ ] Torque
* [ ] Force at point
* [ ] Impulse
* [ ] Torque impulse

---

# PHYS-102 — Mass Properties

### Tasks

* [ ] Mass
* [ ] Inverse Mass
* [ ] Center of Mass
* [ ] Density
* [ ] Volume

### Acceptance Criteria

* [ ] Static bodies supported
* [ ] Infinite mass handling

---

# PHYS-103 — Inertia Tensor

### Tasks

* [ ] Sphere inertia
* [ ] Box inertia
* [ ] Capsule inertia
* [ ] Custom inertia

---

# EPIC — Integration

---

# PHYS-200 — Explicit Euler

### Description

Reference implementation for comparison and debugging.

### Tasks

* [ ] Position integration
* [ ] Velocity integration

---

# PHYS-201 — Semi-Implicit Euler

### Description

Primary integration method.

### Acceptance Criteria

* [ ] Stable under gravity
* [ ] Stable with forces
* [ ] Default integrator

---

# PHYS-202 — Verlet Integration

### Tasks

* [ ] Position Verlet
* [ ] Velocity Verlet

---

# PHYS-203 — RK4 Integration

### Tasks

* [ ] Fourth-order integrator
* [ ] Benchmark accuracy
* [ ] Compare against Euler

---

# EPIC — Collision Shapes

---

# PHYS-300 — Collider Base

### Tasks

* [ ] Base collider
* [ ] Local transform
* [ ] Material
* [ ] Trigger flag

---

# PHYS-301 — Primitive Colliders

### Tasks

* [ ] Sphere
* [ ] Box
* [ ] Capsule
* [ ] Plane

---

# PHYS-302 — Mesh Collider (Future)

### Tasks

* [ ] Triangle mesh
* [ ] Convex mesh
* [ ] Heightmap

---

# EPIC — Broad Phase

---

# PHYS-400 — Broad Phase

### Description

Quickly eliminate impossible collisions.

### Algorithms

* [ ] Brute force (baseline)
* [ ] Sweep and Prune
* [ ] Dynamic AABB Tree
* [ ] BVH (future)

### Acceptance Criteria

* [ ] Pair generation
* [ ] Performance benchmark

---

# EPIC — Narrow Phase

---

# PHYS-500 — Collision Detection

### Tasks

* [ ] Sphere ↔ Sphere
* [ ] Sphere ↔ Box
* [ ] Box ↔ Box (SAT)
* [ ] Capsule ↔ Capsule
* [ ] Raycasts

---

# PHYS-501 — Contact Generation

### Tasks

* [ ] Contact point
* [ ] Contact normal
* [ ] Penetration depth
* [ ] Multiple contacts

---

# PHYS-502 — Contact Manifold

### Tasks

* [ ] Persistent manifold
* [ ] Warm starting
* [ ] Contact caching

---

# PHYS-503 — Continuous Collision Detection

### Tasks

* [ ] Time of Impact
* [ ] Swept sphere
* [ ] Swept AABB
* [ ] Conservative advancement

---

# EPIC — Constraints

---

# PHYS-600 — Spring Constraint

### Tasks

* [ ] Hooke's Law
* [ ] Damping
* [ ] Rest length

---

# PHYS-601 — Distance Joint

### Tasks

* [ ] Fixed distance
* [ ] Soft constraint
* [ ] Break force

---

# PHYS-602 — Hinge Joint

### Tasks

* [ ] Pivot
* [ ] Angular limits
* [ ] Motors

---

# PHYS-603 — Fixed Joint

### Tasks

* [ ] Weld bodies
* [ ] Preserve orientation

---

# EPIC — Constraint Solver

---

# PHYS-700 — Sequential Impulse Solver

### Description

Primary constraint solver inspired by modern real-time physics engines.

### Tasks

* [ ] Sequential impulses
* [ ] Iterative solver
* [ ] Warm starting
* [ ] Bias correction

---

# PHYS-701 — Restitution

### Tasks

* [ ] Bounce coefficient
* [ ] Velocity threshold

---

# PHYS-702 — Friction

### Tasks

* [ ] Static friction
* [ ] Dynamic friction
* [ ] Rolling friction (future)

---

# PHYS-703 — Sleeping

### Tasks

* [ ] Sleep detection
* [ ] Wake-up events
* [ ] Island sleeping

---

# EPIC — Physics Queries

---

# PHYS-800 — Physics Queries

### Tasks

* [ ] Raycast
* [ ] SphereCast
* [ ] BoxCast
* [ ] OverlapSphere
* [ ] OverlapBox
* [ ] ClosestPoint

---

# EPIC — Debugging

---

# PHYS-900 — Physics Debug Renderer

### Tasks

* [ ] Collider wireframes
* [ ] Contact points
* [ ] Contact normals
* [ ] AABBs
* [ ] Center of Mass
* [ ] Sleeping state

---

# PHYS-901 — Physics Profiler

### Tasks

* [ ] Broad phase timing
* [ ] Narrow phase timing
* [ ] Solver timing
* [ ] Body count
* [ ] Collision pair count

---

# Recommended implementation order

This is the order used by many educational and production physics engines because each layer builds on the previous one:

```text
PHYS-001  Physics World
        ↓
PHYS-100  RigidBody
PHYS-101  Force Accumulator
PHYS-102  Mass Properties
PHYS-103  Inertia Tensor
        ↓
PHYS-201  Semi-Implicit Euler
(then PHYS-200/202/203 for comparison and experimentation)
        ↓
PHYS-300  Collider Base
PHYS-301  Primitive Colliders
        ↓
PHYS-400  Broad Phase
        ↓
PHYS-500  Collision Detection
PHYS-501  Contact Generation
PHYS-502  Contact Manifold
        ↓
PHYS-700  Sequential Impulse Solver
PHYS-701  Restitution
PHYS-702  Friction
PHYS-703  Sleeping
        ↓
PHYS-600  Constraints
        ↓
PHYS-800  Physics Queries
        ↓
PHYS-900  Debug Tools
```

## One architectural recommendation

I'd also add one more module that many hobby engines forget:

```text
Physics/
├── Dynamics/
├── Collision/
├── Constraints/
├── Solvers/
├── Queries/
├── Materials/
├── Debug/
└── PhysicsWorld/
```

Notice the **Materials** module. A `PhysicsMaterial` (containing friction, restitution, density, etc.) should be its own asset type rather than fields embedded in every collider. That's how engines like Unity, Unreal, Bullet, PhysX, and Jolt structure their physics systems, and it keeps collision behavior reusable and consistent across different objects.
