```text
Rockets/
│
├── Engine/
│   ├── Core/
│   ├── Math/
│   ├── Platform/
│   ├── Renderer/
│   ├── ECS/
│   ├── Physics/
│   ├── Audio/
│   ├── Scene/
│   ├── Assets/
│   ├── UI/
│   ├── Debug/
│   └── Editor/
│
├── Games/
│   ├── RocketSimulator/
│   ├── Sandbox/
│   └── FutureGames/
│
├── ThirdParty/
├── Assets/
└── Tools/
```

---

# ENGINE ROADMAP

---

# PHASE 0 — FOUNDATION

## Repository

```
[X] Project Structure
[X] CMake
[X] Build Scripts
[ ] GitHub Actions
[ ] Package Manager Integration
[ ] Documentation
[ ] Versioning
```

## Core Utilities

```
[X] Logger
[X] Assertions
[ ] Config System
[ ] Command Line Parser
[ ] UUID
[ ] FileSystem
[ ] Virtual File System
[ ] Memory Allocators
[ ] Job System
```

---

# PHASE 1 — PLATFORM

```
[ ] SDL Platform Layer
[ ] Window
[ ] Monitor Management
[ ] Cursor
[ ] Clipboard
[ ] Drag & Drop
[ ] File Dialog
[ ] Timers
[ ] High Resolution Clock
```

## Events

```
[ ] Event Base Class
[ ] Keyboard Events
[ ] Mouse Events
[ ] Window Events
[ ] Gamepad Events
[ ] Event Dispatcher
```

## Input

```
[ ] Keyboard
[ ] Mouse
[ ] Controller
[ ] Action Mapping
```

---

# PHASE 2 — MATH

Split this into modules instead of one huge section.

---

## Scalars

```
[ ] clamp
[ ] saturate
[ ] lerp
[ ] inverseLerp
[ ] remap
[ ] smoothstep
[ ] smootherstep
[ ] radians/degrees
[ ] epsilon compare
[ ] random
```

---

## Vector

```
[X] Vec2
[X] Vec3
[X] Vec4

[X] Add
[X] Subtract
[X] Multiply
[X] Divide

[X] Dot
[X] Cross

[X] Normalize
[X] Magnitude
[X] Distance

[ ] Angle
[ ] Projection
[ ] Rejection
[ ] Reflection
[ ] Refraction

[ ] Min
[ ] Max
[ ] Clamp

[ ] Rotate
```

---

## Matrix

```
[X] Mat3
[ ] Mat4

[ ] Identity
[ ] Determinant
[ ] Inverse
[ ] Transpose

[ ] Translation
[ ] Scale

[ ] RotationX
[ ] RotationY
[ ] RotationZ
[ ] Axis Angle

[ ] Perspective
[ ] Orthographic

[ ] LookAt

[ ] TRS
```

---

## Quaternion

```
[ ] Identity

[ ] Normalize

[ ] Inverse

[ ] Multiply

[ ] Axis Angle

[ ] Euler

[ ] Matrix Conversion

[ ] Rotate Vector

[ ] SLERP

[ ] NLERP
```

---

## Geometry

```
[ ] Ray
[ ] Plane
[ ] Line
[ ] Segment

[ ] Triangle

[ ] Sphere

[ ] Capsule

[ ] AABB

[ ] OBB

[ ] Frustum
```

---

## Geometry Algorithms

```
[ ] Ray Plane

[ ] Ray Triangle

[ ] Ray Sphere

[ ] Ray AABB

[ ] Ray OBB

[ ] Sphere Sphere

[ ] AABB AABB

[ ] OBB OBB (SAT)

[ ] Closest Point

[ ] Barycentric

[ ] Convex Hull
```

---

## Noise

```
[ ] Perlin

[ ] Simplex

[ ] FBM
```

---

# PHASE 3 — CAMERA

```
[ ] Camera

[ ] View Matrix

[ ] Projection Matrix

[ ] Perspective

[ ] Orthographic

[ ] Orbit Camera

[ ] FPS Camera

[ ] Editor Camera

[ ] ScreenToWorld

[ ] WorldToScreen

[ ] Picking Ray

[ ] Frustum
```

---

# PHASE 4 — RENDERER

## Graphics Device

```
[ ] OpenGL Context

[ ] Render Device

[ ] Render Commands
```

---

## Buffers

```
[ ] Vertex Buffer

[ ] Index Buffer

[ ] Uniform Buffer

[ ] Shader Storage Buffer

[ ] Vertex Array
```

---

## Resources

```
[ ] Texture2D

[ ] Texture Cube

[ ] Material

[ ] Shader

[ ] Mesh
```

---

## Rendering

```
[ ] Triangle

[ ] Cube

[ ] Mesh Rendering

[ ] Wireframe

[ ] Depth

[ ] Face Culling

[ ] Transparency

[ ] Skybox

[ ] Shadows

[ ] Lighting

[ ] PBR
```

---

# PHASE 5 — ECS

```
[ ] Entity

[ ] Component

[ ] World

[ ] Sparse Set

[ ] Query

[ ] Scheduler

[ ] Systems

[ ] Events

[ ] Serialization
```

---

# PHASE 6 — SCENE

```
[ ] Scene

[ ] Entity Hierarchy

[ ] Parent Child

[ ] Transform Propagation

[ ] Prefabs

[ ] Serialization

[ ] Loading

[ ] Saving
```

---

# PHASE 7 — PHYSICS

Notice how there's **nothing about rockets**.

## Dynamics

```
[ ] RigidBody

[ ] Mass

[ ] Forces

[ ] Torque

[ ] Velocity

[ ] Angular Velocity

[ ] Inertia Tensor
```

---

## Integration

```
[ ] Explicit Euler

[ ] Semi-Implicit Euler

[ ] Verlet

[ ] RK4
```

---

## Collision

```
[ ] Broad Phase

[ ] Narrow Phase

[ ] Contacts

[ ] Manifolds

[ ] Continuous Collision
```

---

## Constraints

```
[ ] Spring

[ ] Distance Joint

[ ] Hinge

[ ] Fixed Joint
```

---

## Solver

```
[ ] Impulse Solver

[ ] Restitution

[ ] Friction

[ ] Sleeping
```

---

# PHASE 8 — ASSETS

```
[ ] Asset Manager

[ ] Importers

[ ] Texture Loader

[ ] Mesh Loader

[ ] Shader Loader

[ ] Resource Cache

[ ] Hot Reload
```

---

# PHASE 9 — AUDIO

```
[ ] Audio Device

[ ] Source

[ ] Listener

[ ] Mixer

[ ] Streaming
```

---

# PHASE 10 — UI

```
[ ] Widget System

[ ] Canvas

[ ] Panel

[ ] Label

[ ] Button

[ ] Text Input

[ ] Docking

[ ] Layout
```

---

# PHASE 11 — EDITOR

This is completely separate from the engine.

```
[ ] Scene Hierarchy

[ ] Inspector

[ ] Asset Browser

[ ] Gizmos

[ ] Profiler

[ ] Console

[ ] Material Editor

[ ] Scene View

[ ] Game View

[ ] Toolbar

[ ] Hot Reload

[ ] Undo/Redo
```

---

# PHASE 12 — DEBUG

```
[ ] FPS

[ ] Frame Time

[ ] Memory Viewer

[ ] Physics Debug

[ ] Renderer Debug

[ ] ECS Viewer

[ ] GPU Timers

[ ] CPU Profiler
```

---

# ROCKET SIMULATOR (GAME)

Everything below lives in `Games/RocketSimulator/`.

## World

```
[ ] Planet
[ ] Moon
[ ] Star
[ ] Atmosphere
[ ] Gravity Field
```

---

## Rocket

```
[ ] Rocket
[ ] Part
[ ] Fuel Tank
[ ] Engine
[ ] Decoupler
[ ] Fairing
[ ] Nose Cone
[ ] Wing
[ ] Landing Leg
[ ] Docking Port
```

---

## Physics

```
[ ] Thrust
[ ] ISP
[ ] Fuel Flow
[ ] Center of Mass
[ ] Center of Pressure
[ ] Drag
[ ] Lift
[ ] Staging
[ ] Aerodynamic Heating
```

---

## Flight

```
[ ] SAS
[ ] RCS
[ ] Autopilot
[ ] Maneuver Nodes
[ ] Orbit Prediction
[ ] Time Warp
```

---

## Builder

```
[ ] Part Picker
[ ] Snap System
[ ] Symmetry
[ ] Mirror Mode
[ ] Part Rotation
[ ] Undo/Redo
```

---

## Gameplay

```
[ ] Save/Load
[ ] Missions
[ ] Contracts
[ ] Science
[ ] Sandbox
```


