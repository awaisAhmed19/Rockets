# ===========================
# ROCKETS ENGINE MASTER TODO
# ===========================

# PHASE 0 — PROJECT SETUP
[X] Project structure
[X] CMake
[X] Build scripts
[ ] GitHub Actions
[X] Logger
[X] Assertions
[ ] Config system

# PHASE 1 — CORE
[ ] Application
[ ] Engine
[X] Window
[ ] Platform Layer (SDL)
[ ] Event System
[ ] Input
[ ] Timer
[ ] Fixed Game Loop
[ ] FPS Counter
[ ] Shutdown

# PHASE 2 — MATH
## Vectors
[ ] Vector2
[ ] Vector3
[ ] Vector4

## Matrix
[ ] Matrix3
[ ] Matrix4
[ ] Matrix Inverse
[ ] Matrix Transpose

## Rotation
[ ] Quaternion
[ ] Euler Angles
[ ] Axis Angle
[ ] SLERP

## Geometry
[ ] Ray
[ ] Plane
[ ] Sphere
[ ] AABB
[ ] OBB
[ ] Frustum

## Transform
[ ] Transform
[ ] Local Transform
[ ] World Transform

# PHASE 3 — CAMERA
[ ] View Matrix
[ ] Perspective Projection
[ ] Orthographic Projection
[ ] Free Camera
[ ] Orbit Camera
[ ] FPS Camera
[ ] Camera Controller
[ ] Camera Zoom
[ ] ScreenToWorld()
[ ] WorldToScreen()

# PHASE 4 — RENDERER
## OpenGL Backend
[ ] SDL OpenGL Context
[ ] Renderer
[ ] Render Device

## Buffers
[ ] Vertex Buffer
[ ] Index Buffer
[ ] Vertex Array

## Shaders
[ ] Shader
[ ] Shader Compiler
[ ] Uniform Buffer

## Resources
[ ] Texture2D
[ ] Cubemap
[ ] Material
[ ] Mesh

## Rendering
[ ] Draw Triangle
[ ] Draw Cube
[ ] Mesh Rendering
[ ] Wireframe
[ ] Depth Buffer
[ ] Face Culling
[ ] Basic Lighting

# PHASE 5 — ECS
[ ] Entity
[ ] Component
[ ] System
[ ] World
[ ] Sparse Set
[ ] Archetype Storage
[ ] Query System
[ ] Scheduler

# PHASE 6 — SCENE
[ ] Scene
[ ] Scene Graph
[ ] Parent/Child
[ ] Transform Propagation
[ ] Scene Loading
[ ] Scene Saving
[ ] Prefabs

# PHASE 7 — PHYSICS
## Motion
[ ] Position
[ ] Velocity
[ ] Acceleration
[ ] Force
[ ] Mass

## Integration
[ ] Semi-Implicit Euler
[ ] RK4

## Collision
[ ] Raycast
[ ] Sphere Collision
[ ] AABB Collision
[ ] OBB Collision
[ ] Contact Generation

## Resolution
[ ] Impulse Solver
[ ] Restitution
[ ] Friction

## Constraints
[ ] Springs
[ ] Fixed Joint
[ ] Hinge Joint

## Rocket Physics
[ ] Gravity
[ ] Atmospheric Drag
[ ] Thrust
[ ] Fuel Consumption
[ ] Center of Mass
[ ] Inertia Tensor
[ ] Staging

# PHASE 8 — ASSETS
[ ] Asset Manager
[ ] Texture Loader
[ ] Mesh Loader
[ ] Shader Loader
[ ] Resource Cache
[ ] Hot Reload

# PHASE 9 — AUDIO
[ ] Audio Device
[ ] Audio Source
[ ] Audio Listener
[ ] Mixer

# PHASE 10 — UI
[ ] Canvas
[ ] Button
[ ] Label
[ ] Panel
[ ] Layout

# PHASE 11 — DEBUG
[ ] FPS Overlay
[ ] Memory Viewer
[ ] Entity Viewer
[ ] Physics Debug Draw
[ ] Camera Debug
[ ] Profiler

# PHASE 12 — GAME
[ ] Planet
[ ] Rocket
[ ] Fuel Tank
[ ] Engine
[ ] Thruster
[ ] Flight Computer
[ ] Orbit Prediction
[ ] Docking
[ ] Save/Load
