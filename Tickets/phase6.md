
```text
Engine
│
├── ECS
│   ├── Entity IDs
│   ├── Component Storage
│   ├── Queries
│   ├── Systems
│   └── Scheduler
│
└── Scene
    ├── Scene
    ├── Scene Manager
    ├── Hierarchy
    ├── Transform Graph
    ├── Prefabs
    ├── Serialization
    └── Scene Loading
```



---

# EPIC — Scene Management

---

# SCENE-001 — Scene Class

**Priority:** Critical

### Description

Implement the Scene class as the primary container for entities, systems, and world state.

A scene represents one complete level or world.

### Responsibilities

* Own an ECS World
* Update entities
* Load assets
* Maintain hierarchy
* Control lifecycle

### Public API

```cpp
Scene scene;

scene.Initialize();

scene.Update(dt);

scene.Destroy();

scene.GetWorld();
```

### Tasks

* [ ] Create Scene
* [ ] Destroy Scene
* [ ] Update Scene
* [ ] Pause Scene
* [ ] Resume Scene
* [ ] Reset Scene

### Acceptance Criteria

* [ ] Scene owns a World
* [ ] Proper cleanup
* [ ] Supports multiple scenes

---

# SCENE-002 — Scene Manager

### Description

Manage all active scenes.

### Features

* Create Scene
* Destroy Scene
* Set Active Scene
* Push Scene
* Pop Scene

### Example

```cpp
SceneManager::Push(menuScene);

SceneManager::Push(gameScene);

SceneManager::Pop();
```

### Acceptance Criteria

* [ ] Scene switching
* [ ] Active scene tracking
* [ ] Scene stack

---

# EPIC — Hierarchy

---

# SCENE-100 — Entity Hierarchy

### Description

Maintain parent-child relationships between entities.

### Responsibilities

* Parent
* Child
* Siblings

### API

```cpp
scene.SetParent(child,parent);

scene.RemoveParent(child);

scene.GetChildren(entity);
```

### Tasks

* [ ] Parent
* [ ] Child
* [ ] Remove Parent
* [ ] Enumerate Children
* [ ] Root Entities

### Acceptance Criteria

* [ ] Unlimited hierarchy depth
* [ ] Fast traversal
* [ ] No cycles allowed

---

# SCENE-101 — Hierarchy Validation

### Description

Prevent invalid scene graphs.

### Tasks

* [ ] Detect circular parenting
* [ ] Prevent self-parenting
* [ ] Prevent duplicate parents

### Acceptance Criteria

* [ ] Tree always valid

---

# EPIC — Transform Graph

---

# SCENE-200 — Local Transform

### Description

Store transform relative to parent.

### Data

* Position
* Rotation
* Scale

### Acceptance Criteria

* [ ] Local TRS
* [ ] Dirty flag

---

# SCENE-201 — World Transform

### Description

Compute world transforms.

### Responsibilities

```text
Local

↓

Parent

↓

World
```

### Tasks

* [ ] World Matrix
* [ ] Recursive update
* [ ] Dirty propagation

### Acceptance Criteria

* [ ] Correct hierarchy transforms
* [ ] Efficient updates

---

# SCENE-202 — Transform Propagation

### Description

Update transform hierarchy efficiently.

### Tasks

* [ ] Dirty propagation
* [ ] Breadth-first update
* [ ] Depth-first update
* [ ] Cache matrices

### Acceptance Criteria

* [ ] Only dirty nodes updated
* [ ] Stable update order

---

# EPIC — Prefabs

---

# SCENE-300 — Prefab Asset

### Description

Represent reusable groups of entities.

Example

```text
Rocket

├── FuelTank

├── Engine

├── Camera
```

### Tasks

* [ ] Save prefab
* [ ] Load prefab
* [ ] Instantiate prefab

### Acceptance Criteria

* [ ] Preserve hierarchy
* [ ] Preserve components

---

# SCENE-301 — Prefab Overrides

### Description

Support modifications after instantiation.

### Tasks

* [ ] Track overrides
* [ ] Apply updates
* [ ] Reset overrides

### Acceptance Criteria

* [ ] Base prefab unchanged
* [ ] Instance customization

---

# EPIC — Serialization

---

# SCENE-400 — Scene Serialization

### Description

Serialize the complete scene.

### Contents

* Entities
* Components
* Hierarchy
* Metadata

### Formats

* JSON
* Binary (future)

### Acceptance Criteria

* [ ] Serialize
* [ ] Deserialize
* [ ] Version support

---

# SCENE-401 — Component Serialization

### Tasks

* [ ] Transform
* [ ] Mesh
* [ ] Camera
* [ ] Lights
* [ ] Physics

### Acceptance Criteria

* [ ] Automatic registration
* [ ] Version compatibility

---

# EPIC — Scene Loading

---

# SCENE-500 — Scene Loader

### Description

Load scene assets into memory.

### Tasks

* [ ] Parse file
* [ ] Create entities
* [ ] Create hierarchy
* [ ] Load assets

### Acceptance Criteria

* [ ] Scene loads correctly
* [ ] Missing assets handled

---

# SCENE-501 — Scene Saver

### Description

Save the active scene.

### Tasks

* [ ] Serialize
* [ ] Compress (future)
* [ ] Validate

### Acceptance Criteria

* [ ] Scene identical after reload

---

# EPIC — Runtime

---

# SCENE-600 — Runtime Scene Lifecycle

### Description

Control runtime scene execution.

### Features

* Initialize
* Start
* Update
* FixedUpdate
* LateUpdate
* Shutdown

### Acceptance Criteria

* [ ] Correct execution order
* [ ] Pause support
* [ ] Resume support

---

# EPIC — Debugging

---

# SCENE-700 — Scene Inspector

### Features

* Entity Tree
* Parent Tree
* Component Viewer
* Search
* Selection

### Acceptance Criteria

* [ ] Expand/collapse hierarchy
* [ ] Entity selection
* [ ] Component inspection

---

# SCENE-701 — Scene Debug Tools

### Features

* Draw hierarchy
* Draw transform axes
* Draw bounding boxes
* Draw frustums
* Draw physics

---

# Recommended implementation order

```text
SCENE-001  Scene
        ↓
SCENE-002  Scene Manager
        ↓
SCENE-100  Entity Hierarchy
        ↓
SCENE-101  Hierarchy Validation
        ↓
SCENE-200  Local Transform
        ↓
SCENE-201  World Transform
        ↓
SCENE-202  Transform Propagation
        ↓
SCENE-400  Scene Serialization
        ↓
SCENE-500  Scene Loader
SCENE-501  Scene Saver
        ↓
SCENE-300  Prefabs
SCENE-301  Prefab Overrides
        ↓
SCENE-600  Runtime Lifecycle
        ↓
SCENE-700  Debug Tools
```

## One architectural change I'd recommend

I'd actually **move `Transform` out of the Math module** and make it a **Scene component**.

The layering becomes:

```text
Math
├── Vec2
├── Vec3
├── Vec4
├── Mat4
└── Quaternion

ECS
├── Entity
├── Component Storage
└── Systems

Scene
├── Transform Component
├── Hierarchy
├── Transform Graph
├── Scene
└── Prefabs
```

This keeps responsibilities clean:

* **Math** provides the primitives (`Vec3`, `Mat4`, `Quaternion`).
* **ECS** stores arbitrary components but doesn't know what they mean.
* **Scene** gives semantic meaning to a `Transform` by organizing entities into a hierarchy and computing local/world transforms.

That separation makes your engine much easier to maintain and allows the ECS to remain completely generic.
