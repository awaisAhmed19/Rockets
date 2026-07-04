---

# Level 1 — Development Hot Reload (Very Early)

This should exist almost as soon as your renderer works.

Example:

```text
Ctrl + S shader.glsl

↓

Engine detects file changed

↓

Recompile shader

↓

Replace GPU program

↓

Continue running
```

No restart.

This is a **huge** productivity boost.

I'd implement this immediately after your shader system.

```
REND-203 — Shader Hot Reload
```

Dependencies

```
Shader
Filesystem
Timestamp
```

---

# Level 2 — Asset Hot Reload

Once textures and meshes exist.

```
rocket.png

↓

Save

↓

Reload texture

↓

Update GPU

↓

Continue
```

Same for

```
.obj
.gltf
.png
.jpg
.wav
```

This belongs in the Asset system.

---

# Level 3 — Script/Game Reload

Much later.

This is things like

* Lua
* C#
* DLL reloading

You probably won't need this for a long time.

---

# I'd actually restructure your roadmap

Instead of

```
Renderer

↓

Assets

↓

Hot Reload
```

I'd do

```
Renderer

↓

Shader Hot Reload

↓

Assets

↓

Asset Hot Reload

↓

Editor

↓

Live Editing
```

---

# I would split Assets into these epics

## ASSET-001 — Asset Manager

Responsible for

```
UUID

Reference counting

Asset registry

Lifetime
```

---

## ASSET-002 — Asset Database

Maps

```
UUID

↓

File

↓

Loaded Asset
```

Like Unity's `.meta` files.

---

## ASSET-003 — File Watcher ⭐

This is the important one.

Use

```
Linux

↓

inotify

Windows

↓

ReadDirectoryChangesW

macOS

↓

FSEvents
```

SDL doesn't expose file watching, so this is a platform feature.

Responsibilities

```
Watch directories

Notify changes

Notify deletes

Notify renames
```

---

## ASSET-004 — Texture Loader

Supports

```
PNG

JPEG

BMP

DDS
```

---

## ASSET-005 — Mesh Loader

Supports

```
OBJ

GLTF

FBX (future)
```

---

## ASSET-006 — Shader Loader

Supports

```
Vertex

Fragment

Geometry

Compute (future)
```

---

## ASSET-007 — Resource Cache

```
Texture

↓

Already loaded?

↓

Yes

↓

Return existing pointer
```

instead of loading twice.

---

## ASSET-008 — Shader Hot Reload ⭐⭐⭐⭐⭐

This should be one of the earliest "quality of life" features.

Pipeline

```
File changes

↓

Compile

↓

Link

↓

Swap GPU Program

↓

Keep running
```

---

## ASSET-009 — Texture Hot Reload

```
Save PNG

↓

Reload texture

↓

Update OpenGL texture
```

---

## ASSET-010 — Mesh Hot Reload

```
Modify OBJ

↓

Reload mesh

↓

Update VAO/VBO
```

---

## ASSET-011 — Material Hot Reload

Automatically refresh

```
Shader

Texture

Material Parameters
```

---

## ASSET-012 — Asset Dependency Graph

```
Material

↓

Shader

↓

Textures
```

Reloading the shader automatically updates every material using it.

---

# If I were building Rockets

I'd actually move one ticket **way earlier**.

```
Phase 4
│
├── OpenGL
├── Buffers
├── Shader
├── Shader Hot Reload  ← HERE
├── Texture
├── Mesh
└── Rendering
```

because you'll spend **thousands** of shader recompiles while learning OpenGL.

Having to restart the engine every time becomes painful almost immediately.

---

## One thing I'd change even further

I wouldn't even call this phase **"Assets."** I'd split it into two independent engine modules:

```
Asset/
├── Asset Manager
├── Asset Registry
├── Importers
├── Resource Cache
└── UUID

Resources/
├── Texture
├── Mesh
├── Material
├── Shader
└── Font
```

Why? Because a **Shader** is a GPU resource, not an asset-management concern. Likewise, a `Texture` or `Mesh` is the in-memory representation used by the renderer. The Asset module's job is to locate files, import them, cache them, watch for changes, and manage their lifetime. Keeping those responsibilities separate gives you a cleaner architecture and makes future features like asset pipelines, cooked assets, or editor tooling much easier to build.
