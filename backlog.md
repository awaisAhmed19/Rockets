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
[X] Vector2
[X] Vector3
[ ] Vector4
## Math APIs

**Vector**
[ ] Vector2, Vector3, Vector4
[ ] add, subtract, scale, negate
[ ] dot, cross
[ ] length, lengthSquared, normalize
[ ] lerp, slerp (for directions)
[ ] reflect, refract, project, reject
[ ] distance, distanceSquared
[ ] min, max, clamp (component-wise)
[ ]
**Quaternion**
[ ] multiply, conjugate, inverse, normalize
[ ] fromAxisAngle, fromEuler, fromMatrix
[ ] toMatrix, toEuler
[ ] slerp, nlerp
[ ] rotateVector
[ ]
**Scalar/utility**
[ ] lerp, inverseLerp, remap
[ ] clamp, saturate
[ ] smoothstep, smootherstep
[ ] easing functions (easeIn/Out/InOut variants)
[ ] degrees↔radians
[ ] approxEqual (epsilon compare)
[ ] min, max, abs, sign



## Camera APIs

[ ] setPosition, setRotation/setOrientation (quaternion or Euler)
[ ] lookAt(target, up)
[ ] getViewMatrix, getProjectionMatrix, getViewProjectionMatrix
[ ] setPerspective(fov, aspect, near, far)
[ ] setOrthographic(left, right, bottom, top, near, far)
[ ] getFrustumPlanes (6 planes, for culling)
[ ] screenToWorldRay(screenPos) — unprojection/picking
[ ] worldToScreen(worldPos)
[ ] move/pan (relative translation in local space)
[ ] orbit(target, deltaYaw, deltaPitch, distance)
[ ] zoom(delta) / setFOV
[ ] getForward, getRight, getUp (basis vectors from orientation)
[ ] setNearFar, setAspectRatio
## Matrix
[X] Matrix3
[ ] Matrix4
[ ] Matrix Inverse
[ ] Matrix Transpose
**Matrix**
[ ] Matrix3x3, Matrix4x4
[ ] multiply, transpose, inverse, determinant
[ ] identity, translation, rotationX/Y/Z, rotationAxisAngle, scale
[ ] TRS composition/decomposition
[ ] lookAt
[ ] perspective, orthographic
[ ] transformPoint, transformVector, transformNormal (inverse-transpose)


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
**Geometric primitives**
[ ] AABB — construct, union, overlap, containsPoint, rayIntersect
[ ] OBB — overlap (SAT)
[ ] Sphere, Plane, Ray, Frustum, Capsule
[ ] ray-triangle, ray-sphere, ray-AABB, ray-plane intersection
[ ] sphere-sphere, AABB-AABB overlap
[ ] frustum-AABB, frustum-sphere (culling)
[ ] closestPointOnPlane, closestPointOnSegment
[ ] barycentricCoordinates

**Random/noise**
[ ] PerlinNoise, SimplexNoise
[ ] randomRange, randomUnitVector, randomInsideSphere
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
