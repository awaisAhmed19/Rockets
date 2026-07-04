
split **Camera** into **three epics**:

* **CAM** – Camera Mathematics & API
* **CTRL** – Camera Controllers
* **CULL** – Visibility & Picking

This mirrors how most engines separate concerns. The camera shouldn't know *how* it's controlled (FPS, orbit, editor); those are controllers built on top of a generic camera.

---
# EPIC — Camera System
---

# CAM-001 — Camera Class
**Priority:** Critical

### Description

Implement the engine's generic camera class. This class stores the camera's transform and projection parameters but contains no game-specific movement logic.

### Responsibilities

* Position
* Orientation (Quaternion)
* Near/Far planes
* Aspect ratio
* Projection type

### Public API

```cpp
Camera camera;

camera.SetPosition();

camera.SetRotation();

camera.SetPerspective();

camera.SetOrthographic();

camera.LookAt();

camera.GetViewMatrix();

camera.GetProjectionMatrix();

camera.GetViewProjectionMatrix();
```

### Acceptance Criteria

* [ ] Camera stores transform
* [ ] Camera stores projection settings
* [ ] Camera supports dirty flags
* [ ] Unit tested

---

# CAM-002 — View Matrix

### Description

Compute the camera's view matrix from its transform.

### Topics

* Camera transform
* World space → View space
* Inverse transform
* LookAt derivation

### Acceptance Criteria

* [ ] View matrix generated correctly
* [ ] Quaternion support
* [ ] Euler support (optional)
* [ ] Unit tests

---

# CAM-003 — Projection Matrix

### Description

Implement the projection pipeline.

### Responsibilities

* Perspective projection
* Orthographic projection
* Projection switching

### Acceptance Criteria

* [ ] Matrix generation
* [ ] Near/Far validation
* [ ] Aspect ratio updates
* [ ] Unit tests

---

# CAM-004 — Perspective Projection

### Features

* Vertical FOV
* Horizontal FOV conversion
* Aspect ratio
* Near plane
* Far plane

### Acceptance Criteria

* [ ] Correct OpenGL projection
* [ ] Adjustable FOV
* [ ] Runtime updates

---

# CAM-005 — Orthographic Projection

### Features

* Left
* Right
* Top
* Bottom
* Near
* Far

### Acceptance Criteria

* [ ] Runtime resizing
* [ ] Pixel-perfect mode (future)
* [ ] UI rendering support

---

# CAM-006 — LookAt Utility

### Description

Generate a camera orientation from an eye position, target position, and up vector.

### Acceptance Criteria

* [ ] Eye position
* [ ] Target
* [ ] Up vector
* [ ] Quaternion output
* [ ] Matrix output

---

# CAM-007 — View Frustum

### Description

Extract frustum planes from the view-projection matrix.

### Features

* Left plane
* Right plane
* Top plane
* Bottom plane
* Near plane
* Far plane

### Acceptance Criteria

* [ ] Six normalized planes
* [ ] Plane extraction
* [ ] Unit tests

---

# CAM-008 — Coordinate Conversion

### Description

Convert between coordinate spaces.

### API

```cpp
WorldToView()

ViewToWorld()

WorldToScreen()

ScreenToWorld()
```

### Acceptance Criteria

* [ ] Correct viewport conversion
* [ ] Inverse projection
* [ ] Window resize support

---

# CAM-009 — Picking Ray

### Description

Generate a ray from a screen coordinate into world space.

### Features

* Mouse picking
* Object selection
* Physics raycasts

### API

```cpp
Ray Camera::ScreenPointToRay(vec2 mousePosition);
```

### Acceptance Criteria

* [ ] Screen coordinates
* [ ] World ray
* [ ] Normalized direction
* [ ] Unit tests

---

# EPIC — Camera Controllers

---

# CTRL-001 — Free Camera Controller

### Description

A camera that can move freely in 3D space.

### Controls

* WASD
* QE (up/down)
* Mouse look
* Speed adjustment

### Acceptance Criteria

* [ ] Smooth movement
* [ ] Configurable speed
* [ ] Delta-time independent

---

# CTRL-002 — FPS Camera Controller

### Description

First-person camera controller.

### Features

* Mouse look
* WASD movement
* Pitch clamp
* Sprint modifier
* Crouch (future)

### Acceptance Criteria

* [ ] Pitch clamped
* [ ] No roll
* [ ] Smooth rotation

---

# CTRL-003 — Orbit Camera Controller

### Description

Orbit around a target point.

### Features

* Rotate
* Pan
* Zoom
* Focus target

### Acceptance Criteria

* [ ] Left-click orbit
* [ ] Middle-click pan
* [ ] Mouse-wheel zoom
* [ ] Adjustable sensitivity

---

# CTRL-004 — Editor Camera

### Description

A camera designed for the engine editor, combining orbit, free-fly, and pan controls.

### Features

* Orbit
* Fly mode
* Pan
* Zoom
* Focus selected object
* Frame all objects

### Acceptance Criteria

* [ ] Mimics common DCC/editor workflows
* [ ] Smooth transitions
* [ ] Configurable controls

---

# EPIC — Visibility & Culling

---

# CULL-001 — Frustum Culling

### Description

Determine whether objects are visible inside the camera frustum.

### Supported Tests

* Sphere vs Frustum
* AABB vs Frustum
* OBB vs Frustum (future)

### Acceptance Criteria

* [ ] Cull spheres
* [ ] Cull AABBs
* [ ] Plane-based testing
* [ ] Performance benchmark

---

# CULL-002 — Visibility System

### Description

Use frustum culling to build the list of visible renderable objects each frame.

### Responsibilities

* Traverse scene
* Test visibility
* Build render list

### Acceptance Criteria

* [ ] Invisible objects skipped
* [ ] Render list generated
* [ ] Debug visualization available

---

# CULL-003 — Camera Debug Visualization

### Description

Render debug representations of the camera and its viewing volume.

### Features

* Camera gizmo
* Frustum wireframe
* Picking ray
* Near/Far planes
* View axes

### Acceptance Criteria

* [ ] Toggleable debug rendering
* [ ] Accurate frustum visualization
* [ ] Picking ray display

---

# Recommended implementation order

Unlike the earlier phases, the camera system has clear dependencies. I'd build it in this sequence:

1. **CAM-001** — Camera Class
2. **CAM-002** — View Matrix
3. **CAM-003** — Projection Matrix
4. **CAM-004** — Perspective Projection
5. **CAM-005** — Orthographic Projection
6. **CAM-006** — LookAt Utility
7. **CAM-008** — Coordinate Conversion
8. **CAM-009** — Picking Ray
9. **CAM-007** — View Frustum
10. **CTRL-001** — Free Camera
11. **CTRL-002** — FPS Camera
12. **CTRL-003** — Orbit Camera
13. **CTRL-004** — Editor Camera
14. **CULL-001** → **CULL-003** — Frustum culling and debug visualization

That order gets you a functional camera for rendering first, then progressively adds interaction, editor usability, and finally rendering optimizations.
