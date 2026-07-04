
```
Renderer
├── Graphics API
├── GPU Resources
├── Shader System
├── Asset Resources
├── Render Pipeline
├── Lighting
├── Materials
└── Advanced Rendering
```
---

# EPIC — Graphics Device

---

# REND-001 — OpenGL Context

**Priority:** Critical

### Description

Initialize the OpenGL backend and create a valid rendering context through SDL.

### Responsibilities

* Create OpenGL context
* Load OpenGL functions
* Query capabilities
* Configure default state

### Tasks

* [ ] Request OpenGL 4.6 Core Profile
* [ ] Create SDL OpenGL Context
* [ ] Initialize GLAD
* [ ] Enable Debug Context
* [ ] Enable VSync
* [ ] Query GPU Vendor
* [ ] Query Renderer
* [ ] Query OpenGL Version
* [ ] Query GLSL Version
* [ ] Query Limits (Textures, UBOs, SSBOs)

### Acceptance Criteria

* [ ] OpenGL initialized
* [ ] Debug callback works
* [ ] GPU information logged

---

# REND-002 — Render Device

### Description

Abstract OpenGL behind a renderer API.

### Responsibilities

```cpp
Renderer::Init();

Renderer::Shutdown();

Renderer::BeginFrame();

Renderer::EndFrame();

Renderer::Present();
```

### Tasks

* [ ] Renderer initialization
* [ ] Renderer shutdown
* [ ] Begin Frame
* [ ] End Frame
* [ ] Present

### Acceptance Criteria

* [ ] Renderer independent of SDL
* [ ] Platform-independent interface

---

# REND-003 — Render Commands

### Description

Centralize all GPU state changes.

### Examples

```cpp
RenderCommand::Clear();

RenderCommand::SetViewport();

RenderCommand::DrawIndexed();

RenderCommand::SetDepthTest();
```

### Tasks

* [ ] Clear Color
* [ ] Clear Depth
* [ ] Viewport
* [ ] Draw Arrays
* [ ] Draw Indexed
* [ ] Polygon Mode
* [ ] Line Width
* [ ] Point Size

---

# EPIC — GPU Buffers

---

# REND-100 — Vertex Buffer

### Tasks

* [ ] Create
* [ ] Destroy
* [ ] Bind
* [ ] Unbind
* [ ] Upload Data
* [ ] Update Data
* [ ] Dynamic Buffers

---

# REND-101 — Index Buffer

### Tasks

* [ ] Create
* [ ] Upload
* [ ] Count
* [ ] Bind
* [ ] Destroy

---

# REND-102 — Vertex Array

### Tasks

* [ ] Create
* [ ] Attribute Layout
* [ ] Enable Attributes
* [ ] Bind
* [ ] Destroy

---

# REND-103 — Uniform Buffer

### Tasks

* [ ] Create
* [ ] Bind
* [ ] Update
* [ ] Binding Points
* [ ] Shared Camera Data

---

# REND-104 — Shader Storage Buffer

### Tasks

* [ ] Create
* [ ] Bind
* [ ] Read
* [ ] Write
* [ ] Compute Shader Support (future)

---

# EPIC — Shader System

---

# REND-200 — Shader Class

### Tasks

* [ ] Load File
* [ ] Compile
* [ ] Link
* [ ] Error Reporting
* [ ] Reflection
* [ ] Hot Reload (future)

---

# REND-201 — Uniform Management

### Tasks

* [ ] int
* [ ] float
* [ ] vec2
* [ ] vec3
* [ ] vec4
* [ ] mat3
* [ ] mat4
* [ ] arrays

---

# REND-202 — Shader Library

### Tasks

* [ ] Cache shaders
* [ ] Prevent duplicate compilation
* [ ] Default shaders

---

# EPIC — Rendering Resources

---

# REND-300 — Texture2D

### Tasks

* [ ] Create
* [ ] Destroy
* [ ] Bind
* [ ] Filtering
* [ ] Wrapping
* [ ] Mipmaps

---

# REND-301 — Cubemap

### Tasks

* [ ] Load six faces
* [ ] Bind
* [ ] Skybox support

---

# REND-302 — Mesh

### Tasks

* [ ] Vertex layout
* [ ] Index data
* [ ] Bounding box
* [ ] GPU upload

---

# REND-303 — Material

### Tasks

* [ ] Shader reference
* [ ] Texture bindings
* [ ] Uniform overrides
* [ ] Material properties

---

# EPIC — Primitive Rendering

---

# REND-400 — Triangle Rendering

### Tasks

* [ ] Render triangle
* [ ] Colored triangle
* [ ] Textured triangle

---

# REND-401 — Cube Rendering

### Tasks

* [ ] Generate cube
* [ ] Render cube
* [ ] Textured cube

---

# REND-402 — Mesh Rendering

### Tasks

* [ ] Draw Mesh
* [ ] Multiple Meshes
* [ ] Instancing (future)

---

# EPIC — GPU Pipeline States

---

# REND-500 — Depth Buffer

### Tasks

* [ ] Enable
* [ ] Disable
* [ ] Depth Function
* [ ] Depth Write
* [ ] Clear Depth

---

# REND-501 — Face Culling

### Tasks

* [ ] Back-face
* [ ] Front-face
* [ ] Winding Order
* [ ] Disable

---

# REND-502 — Blending & Transparency

### Tasks

* [ ] Alpha Blend
* [ ] Additive Blend
* [ ] Premultiplied Alpha
* [ ] Blend Modes

---

# REND-503 — Rasterizer State

### Tasks

* [ ] Fill Mode
* [ ] Wireframe
* [ ] Point Mode
* [ ] Polygon Offset

---

# EPIC — Lighting

---

# REND-600 — Basic Lighting

### Tasks

* [ ] Ambient
* [ ] Diffuse
* [ ] Specular
* [ ] Blinn-Phong

---

# REND-601 — Light Types

### Tasks

* [ ] Directional Light
* [ ] Point Light
* [ ] Spot Light

---

# REND-602 — Shadow Mapping

### Tasks

* [ ] Depth Map
* [ ] Shadow Pass
* [ ] PCF Filtering
* [ ] Cascaded Shadows (future)

---

# EPIC — Advanced Rendering

---

# REND-700 — Skybox

### Tasks

* [ ] Cubemap Loader
* [ ] Skybox Shader
* [ ] Render Skybox

---

# REND-701 — Physically Based Rendering (PBR)

### Tasks

* [ ] Metallic Workflow
* [ ] Roughness
* [ ] Albedo
* [ ] Normal Map
* [ ] AO
* [ ] Emissive

---

# REND-702 — HDR Rendering

### Tasks

* [ ] Floating Point Framebuffer
* [ ] Tone Mapping
* [ ] Exposure

---

# REND-703 — Post Processing

### Tasks

* [ ] Framebuffer
* [ ] Bloom
* [ ] FXAA
* [ ] Gamma Correction
* [ ] Color Grading

---

# REND-704 — Deferred Rendering (Optional)

### Tasks

* [ ] G-Buffer
* [ ] Geometry Pass
* [ ] Lighting Pass
* [ ] SSAO (future)

---

# Suggested implementation order

One thing I'd change from your original list is the order. I'd build the renderer exactly like the OpenGL pipeline grows:

```
REND-001  OpenGL Context
        ↓
REND-002  Render Device
        ↓
REND-003  Render Commands
        ↓
REND-100  Vertex Buffer
REND-101  Index Buffer
REND-102  Vertex Array
        ↓
REND-200  Shader Class
REND-201  Uniforms
        ↓
REND-300  Texture2D
REND-302  Mesh
REND-303  Material
        ↓
REND-400  Triangle
REND-401  Cube
REND-402  Mesh Rendering
        ↓
REND-500  Depth
REND-501  Face Culling
REND-502  Transparency
        ↓
REND-600  Lighting
REND-601  Light Types
        ↓
REND-700+ Advanced Rendering
```

This roadmap also aligns closely with the order used in *LearnOpenGL*, but with an engine architecture layered on top rather than writing everything directly in application code. By the time you reach the `REND-700` series, you'll have a renderer capable of supporting a modern 3D game without needing to redesign its foundations.
