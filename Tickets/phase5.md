---

# EPIC — Entity Management

---

# ECS-001 — Entity ID System

**Priority:** Critical

### Description

Implement lightweight entity handles that uniquely identify every object in the world.

### Responsibilities

* Entity creation
* Entity destruction
* Entity versioning
* Entity validity checking

### API

```cpp
Entity entity = world.CreateEntity();

world.DestroyEntity(entity);

entity.IsValid();
```

### Tasks

* [ ] Entity ID
* [ ] Version number
* [ ] Null entity
* [ ] Equality operators
* [ ] Hash support

### Acceptance Criteria

* [ ] IDs reused safely
* [ ] Destroyed entities become invalid
* [ ] O(1) validity check

---

# ECS-002 — Entity Lifecycle

### Description

Manage creation and destruction of entities.

### Tasks

* [ ] Create
* [ ] Destroy
* [ ] Recycle IDs
* [ ] Deferred destruction
* [ ] Bulk destruction

### Acceptance Criteria

* [ ] No memory leaks
* [ ] Stable ID reuse
* [ ] Deferred deletion supported

---

# EPIC — Component Storage

---

# ECS-100 — Component Base

### Description

Define component requirements and registration.

### Tasks

* [ ] Component registration
* [ ] Component IDs
* [ ] Component traits
* [ ] Component metadata

### Acceptance Criteria

* [ ] Unique component IDs
* [ ] Compile-time registration

---

# ECS-101 — Sparse Set Storage

### Description

Implement cache-friendly sparse set storage.

### Data Layout

```text
Sparse
Dense
Components
```

### Tasks

* [ ] Insert
* [ ] Remove
* [ ] Contains
* [ ] Lookup
* [ ] Dense iteration

### Acceptance Criteria

* [ ] O(1) insertion
* [ ] O(1) removal
* [ ] O(1) lookup
* [ ] Cache-friendly iteration

---

# ECS-102 — Component Manager

### Description

Manage all component pools.

### Tasks

* [ ] Register component
* [ ] Add component
* [ ] Remove component
* [ ] Has component
* [ ] Get component

### API

```cpp
world.Add<Transform>(entity);

world.Remove<Mesh>(entity);

world.Has<Rigidbody>(entity);
```

### Acceptance Criteria

* [ ] Type-safe
* [ ] Template API
* [ ] No RTTI

---

# EPIC — World

---

# ECS-200 — World

### Description

The World owns entities, component pools, and systems.

### Responsibilities

* Entity storage
* Component storage
* Systems
* Event routing

### Tasks

* [ ] Create world
* [ ] Destroy world
* [ ] Update world
* [ ] Reset world

---

# ECS-201 — Multiple Worlds

### Description

Support multiple isolated worlds.

Examples

```text
Editor

Game

Physics Preview

UI
```

### Acceptance Criteria

* [ ] Worlds isolated
* [ ] Independent updates

---

# EPIC — Queries

---

# ECS-300 — Query API

### Description

Iterate efficiently over matching entities.

### API

```cpp
for(auto entity :
world.Query<Transform, Mesh>())
{

}
```

### Tasks

* [ ] Single component
* [ ] Multiple components
* [ ] Include filters
* [ ] Exclude filters

### Acceptance Criteria

* [ ] Cache-friendly
* [ ] Zero allocations

---

# ECS-301 — Views

### Description

Provide reusable cached views over component combinations.

### Tasks

* [ ] Cached iteration
* [ ] Rebuild on structural changes

---

# EPIC — Systems

---

# ECS-400 — System Base

### Description

Base interface for all ECS systems.

### API

```cpp
class PhysicsSystem :

public System
{

};
```

### Tasks

* [ ] Initialize
* [ ] Update
* [ ] Shutdown

---

# ECS-401 — System Manager

### Description

Register and execute systems.

### Tasks

* [ ] Register
* [ ] Remove
* [ ] Enable
* [ ] Disable

### Acceptance Criteria

* [ ] Automatic lifetime
* [ ] Ordered execution

---

# ECS-402 — Scheduler

### Description

Determine execution order of systems.

### Features

* Dependencies
* Fixed update
* Variable update
* Parallel execution (future)

### Tasks

* [ ] Dependency graph
* [ ] Topological sort
* [ ] Fixed timestep support

---

# EPIC — Events

---

# ECS-500 — ECS Events

### Description

Notify systems about structural changes.

### Events

```text
EntityCreated

EntityDestroyed

ComponentAdded

ComponentRemoved
```

### Acceptance Criteria

* [ ] Subscribe
* [ ] Publish
* [ ] Deferred dispatch

---

# ECS-501 — Signals

### Description

Fast callbacks for component lifecycle events.

### Tasks

* [ ] OnConstruct
* [ ] OnDestroy
* [ ] OnReplace

---

# EPIC — Serialization

---

# ECS-600 — Entity Serialization

### Description

Serialize entities and components.

### Formats

* JSON
* Binary (future)

### Tasks

* [ ] Serialize entity
* [ ] Deserialize entity
* [ ] Serialize components

---

# ECS-601 — Prefab Serialization

### Description

Allow groups of entities to be stored as reusable prefabs.

### Tasks

* [ ] Save prefab
* [ ] Load prefab
* [ ] Instantiate prefab

---

# EPIC — Debugging

---

# ECS-700 — ECS Inspector

### Description

Provide runtime inspection of ECS state.

### Features

* Entity list
* Components
* Component counts
* Memory usage
* Query statistics

---

# ECS-701 — ECS Profiler

### Description

Measure ECS performance.

### Statistics

* Entity count
* Component count
* Iteration time
* Cache misses (future)
* Memory usage

---

# Suggested implementation order

Unlike rendering, ECS has a very strict dependency chain. I'd build it like this:

```text
ECS-001  Entity ID System
        ↓
ECS-002  Entity Lifecycle
        ↓
ECS-100  Component Registration
        ↓
ECS-101  Sparse Set Storage
        ↓
ECS-102  Component Manager
        ↓
ECS-200  World
        ↓
ECS-300  Query API
        ↓
ECS-400  System Base
        ↓
ECS-401  System Manager
        ↓
ECS-402  Scheduler
        ↓
ECS-500  ECS Events
        ↓
ECS-600  Serialization
        ↓
ECS-700  Debug Tools
```

## One recommendation for your engine

Since you're aiming to build a **general-purpose engine**, I'd keep **`Transform` out of the ECS module**. `Transform` should be a normal component that lives in your **Scene** module, not something hardcoded into ECS itself.

Your ECS should only know that it stores arbitrary component types. It shouldn't know or care whether a component is a `Transform`, `MeshRenderer`, `RigidBody`, or `RocketEngine`. That separation keeps the ECS reusable for any kind of application—not just games.
