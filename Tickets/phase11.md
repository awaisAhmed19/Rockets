


> **The Editor is NOT the engine.**
>
> The Editor is just another application that links against the engine.


```text
Nebula/
│
├── Engine/
│
├── Editor/
│   ├── Panels/
│   ├── Gizmos/
│   ├── Commands/
│   ├── Viewports/
│   └── Tools/
│
└── Games/
    └── RocketSimulator/
```

---

# PHASE 11 — EDITOR


---

# EPIC — Editor Framework

---

# EDIT-001 — Editor Application

**Priority:** Critical

### Description

Implement the standalone editor application.

### Responsibilities

* Launch engine
* Load projects
* Manage editor windows
* Initialize editor modules

### Tasks

* [ ] Editor startup
* [ ] Shutdown
* [ ] Project loading
* [ ] Dockspace creation
* [ ] Workspace persistence

### Acceptance Criteria

* [ ] Editor launches independently
* [ ] Loads empty project
* [ ] Clean shutdown

---

# EPIC — Scene Hierarchy

---

# EDIT-100 — Scene Hierarchy Panel

### Tasks

* [ ] Tree View
* [ ] Expand/Collapse
* [ ] Rename
* [ ] Delete
* [ ] Search
* [ ] Drag Parenting
* [ ] Context Menu

### Acceptance Criteria

* [ ] Reflects active scene
* [ ] Live updates
* [ ] Supports hierarchy changes

---

# EPIC — Inspector

---

# EDIT-200 — Inspector Panel

### Tasks

* [ ] Entity properties
* [ ] Component list
* [ ] Add Component
* [ ] Remove Component
* [ ] Component folding
* [ ] Multi-selection (future)

---

# EDIT-201 — Property Editors

### Editors

* [ ] Bool
* [ ] Integer
* [ ] Float
* [ ] Vec2
* [ ] Vec3
* [ ] Vec4
* [ ] Quaternion
* [ ] Color
* [ ] Enum
* [ ] Asset Reference

---

# EPIC — Asset Browser

---

# EDIT-300 — Asset Browser

### Tasks

* [ ] Folder tree
* [ ] Search
* [ ] Drag & Drop
* [ ] Rename
* [ ] Delete
* [ ] Create folders

---

# EDIT-301 — Asset Preview

### Tasks

* [ ] Texture preview
* [ ] Mesh preview
* [ ] Material preview
* [ ] Audio preview
* [ ] Shader preview

---

# EPIC — Viewports

---

# EDIT-400 — Scene View

### Features

* [ ] Editor camera
* [ ] Grid
* [ ] Gizmos
* [ ] Object selection
* [ ] Frame selected
* [ ] Render overlays

---

# EDIT-401 — Game View

### Tasks

* [ ] Runtime rendering
* [ ] Resolution scaling
* [ ] Aspect lock
* [ ] Pause
* [ ] Play
* [ ] Step Frame

---

# EPIC — Gizmos

---

# EDIT-500 — Transform Gizmos

### Tasks

* [ ] Translate
* [ ] Rotate
* [ ] Scale
* [ ] Local mode
* [ ] World mode
* [ ] Snapping

---

# EDIT-501 — Physics Gizmos

### Tasks

* [ ] Collider wireframes
* [ ] COM
* [ ] Velocity
* [ ] Contact points

---

# EDIT-502 — Camera Gizmos

### Tasks

* [ ] Frustum
* [ ] Rays
* [ ] Camera icon

---

# EPIC — Console

---

# EDIT-600 — Console Panel

### Tasks

* [ ] Logs
* [ ] Filtering
* [ ] Search
* [ ] Stack traces
* [ ] Clear
* [ ] Copy

---

# EPIC — Material Editor

---

# EDIT-700 — Material Editor

### Tasks

* [ ] Shader assignment
* [ ] Texture slots
* [ ] Uniform editing
* [ ] Preview sphere
* [ ] Save material

---

# EPIC — Toolbar

---

# EDIT-800 — Toolbar

### Buttons

* [ ] Play
* [ ] Pause
* [ ] Stop
* [ ] Step
* [ ] Save
* [ ] Open

---

# EPIC — Live Development

---

# EDIT-900 — Hot Reload Integration

### Tasks

* [ ] Reload shaders
* [ ] Reload textures
* [ ] Reload meshes
* [ ] Reload materials
* [ ] Reload scenes

---

# EDIT-901 — Undo / Redo

### Description

Implement a command-based undo/redo system.

### Commands

* [ ] Create Entity
* [ ] Delete Entity
* [ ] Rename
* [ ] Transform
* [ ] Component Add
* [ ] Component Remove

### Acceptance Criteria

* [ ] Unlimited undo
* [ ] Command history
* [ ] Grouped operations

---

# PHASE 12 — DEBUG

This is another subsystem, not just a checklist.

---

# EPIC — Performance

---

# DEBUG-001 — Performance Overlay

### Tasks

* [ ] FPS
* [ ] Frame Time
* [ ] CPU Time
* [ ] GPU Time
* [ ] Draw Calls
* [ ] Triangle Count

---

# DEBUG-002 — Profiler

### Tasks

* [ ] CPU Timeline
* [ ] GPU Timeline
* [ ] Instrumentation
* [ ] Thread View

---

# EPIC — Memory

---

# DEBUG-100 — Memory Viewer

### Tasks

* [ ] Total allocations
* [ ] Live allocations
* [ ] Heap usage
* [ ] Pool usage
* [ ] Leak detection

---

# EPIC — Renderer

---

# DEBUG-200 — Renderer Debug

### Tasks

* [ ] Wireframe
* [ ] Normals
* [ ] UVs
* [ ] Overdraw
* [ ] Render passes

---

# DEBUG-201 — GPU Diagnostics

### Tasks

* [ ] GPU timers
* [ ] Pipeline statistics
* [ ] Shader compile times

---

# EPIC — Physics

---

# DEBUG-300 — Physics Debug

### Tasks

* [ ] AABBs
* [ ] OBBs
* [ ] Contact points
* [ ] Contact normals
* [ ] Sleeping bodies
* [ ] COM

---

# EPIC — ECS

---

# DEBUG-400 — ECS Viewer

### Tasks

* [ ] Entity count
* [ ] Component counts
* [ ] Queries
* [ ] Systems
* [ ] Archetypes (future)

---

# EPIC — Logging

---

# DEBUG-500 — Debug Console

### Tasks

* [ ] Commands
* [ ] Variables
* [ ] Cvars
* [ ] Runtime diagnostics

---

# ROCKET SIMULATOR

I would actually **rewrite this entire section**.

Instead of organizing by gameplay features, organize by **game systems**.

---

# EPIC — Celestial Bodies

## GAME-100

### Bodies

* [ ] Planet
* [ ] Moon
* [ ] Star
* [ ] Asteroid
* [ ] Space Station

### Environment

* [ ] Atmosphere
* [ ] Gravity Field
* [ ] SOI (Sphere of Influence)
* [ ] Terrain
* [ ] Biomes

---

# EPIC — Vehicle System

## GAME-200

### Parts

* [ ] Fuel Tank
* [ ] Engine
* [ ] Wing
* [ ] Landing Leg
* [ ] Decoupler
* [ ] Docking Port
* [ ] Fairing
* [ ] Solar Panel
* [ ] Battery
* [ ] Reaction Wheel
* [ ] RCS Thruster
* [ ] Payload

---

# EPIC — Vehicle Physics

## GAME-300

### Propulsion

* [ ] Thrust
* [ ] ISP
* [ ] Fuel Flow
* [ ] Throttle Curves

### Aerodynamics

* [ ] Drag
* [ ] Lift
* [ ] Heating
* [ ] Shockwaves (future)

### Mass

* [ ] COM
* [ ] COP
* [ ] Inertia Tensor
* [ ] Dynamic Mass

---

# EPIC — Orbital Mechanics

## GAME-400

* [ ] Two-body physics
* [ ] Patched conics
* [ ] SOI transitions
* [ ] Orbit prediction
* [ ] Maneuver nodes
* [ ] Transfer planning

---

# EPIC — Flight Computer

## GAME-500

* [ ] SAS
* [ ] RCS
* [ ] PID Controllers
* [ ] Autopilot
* [ ] Target tracking

---

# EPIC — Vehicle Builder

## GAME-600

* [ ] Part palette
* [ ] Drag & Drop
* [ ] Snap System
* [ ] Symmetry
* [ ] Mirror
* [ ] Rotation gizmo
* [ ] Undo
* [ ] Redo

---

# EPIC — Save System

## GAME-700

* [ ] Save Vehicle
* [ ] Load Vehicle
* [ ] Save World
* [ ] Save Campaign

---

# EPIC — Gameplay

## GAME-800

* [ ] Sandbox
* [ ] Career
* [ ] Science
* [ ] Contracts
* [ ] Achievements
* [ ] Tech Tree

---

## One thing I'd change if this were my project


```text
PHASE 8 — Animation
├── Skeleton
├── Bones
├── Skinning
├── Animation Clips
├── Animator
├── Blend Trees
├── State Machine
└── IK (future)

PHASE 9 — Assets
```

