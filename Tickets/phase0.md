
# EPIC 0 — Foundation

---

# CORE-001 — Configure Continuous Integration

**Type**

> Chore

**Priority**

> Medium

**Estimate**

> 2–4 hours

### Description

Create a GitHub Actions workflow that automatically builds the engine on every push and pull request.

### Requirements

* Linux build
* Debug build
* Release build
* CMake configure
* CMake build
* Fail on compilation errors

### Acceptance Criteria

* [ ] Workflow exists
* [ ] Push triggers workflow
* [ ] Pull requests trigger workflow
* [ ] Build passes
* [ ] Artifacts uploaded (optional)

### Deliverables

```text
.github/workflows/build.yml
```

---

# CORE-002 — Package Manager Integration

**Type**

Infrastructure

**Priority**

Low

**Estimate**

1 day

### Description

Provide dependency management without committing third-party libraries into the repository.

Initially support:

* SDL3
* OpenGL loader
* stb
* Assimp
* Dear ImGui

### Research

Compare

* vcpkg
* Conan
* CPM.cmake
* FetchContent

Choose one.

### Acceptance Criteria

* [ ] Dependencies install automatically
* [ ] Fresh clone builds
* [ ] README updated

---

# CORE-003 — Documentation Framework

**Priority**

Medium

### Description

Create documentation structure for the engine.

### Tasks

* README
* Folder overview
* Build guide
* Coding standards
* Naming conventions
* Module architecture

### Stretch Goals

* Doxygen
* UML diagrams

### Acceptance Criteria

* [ ] New developer can build engine
* [ ] Coding guidelines documented
* [ ] Architecture diagram added

---

# CORE-004 — Semantic Versioning

**Description**

Introduce version information into the engine.

### Requirements

Support

```text
Major
Minor
Patch
Commit Hash
Build Type
```

Example

```text
Nebula Engine

Version 0.2.4

Commit
f84ac19

Debug Build
```

### Acceptance Criteria

* [ ] Version header
* [ ] Build embeds version
* [ ] Logger prints version

---

# CORE-005 — Configuration System

**Priority**

High

### Description

Centralized configuration system for engine initialization.

Example

```ini
Window.Width=1280
Window.Height=720

Renderer.API=OpenGL

Renderer.VSync=true

Physics.FixedTimeStep=0.016666

Audio.MasterVolume=0.75
```

### Requirements

Support

* bool
* int
* float
* string

### Future

* JSON
* YAML
* Hot reload

### Acceptance Criteria

* [ ] Load config file
* [ ] Save config file
* [ ] Query values
* [ ] Default values
* [ ] Missing key handling

---

# CORE-006 — Command Line Parser

### Description

Allow engine startup configuration through command-line arguments.

Example

```bash
RocketSimulator --fullscreen

RocketSimulator --vsync

RocketSimulator --width 1920

RocketSimulator --height 1080

RocketSimulator --scene sandbox.scene
```

### Acceptance Criteria

* [ ] Flag parsing
* [ ] Value parsing
* [ ] Unknown argument handling
* [ ] Help output

---

# CORE-007 — UUID System

### Description

Create universally unique IDs for engine resources.

Used by

* Assets
* Entities
* Scenes
* Prefabs

Example

```cpp
UUID id = UUID::Generate();
```

### Acceptance Criteria

* [ ] 64-bit or 128-bit UUID
* [ ] Equality operators
* [ ] Hash support
* [ ] String conversion

---

# CORE-008 — File System API

### Description

Create an abstraction over filesystem operations.

Engine code should never call `std::filesystem` directly.

Example

```cpp
File::Exists()

File::Read()

File::Write()

Directory::Create()
```

### Required Features

* Exists
* Copy
* Move
* Delete
* Read
* Write
* Enumerate

### Acceptance Criteria

* [ ] Cross-platform
* [ ] UTF-8 support
* [ ] Binary files
* [ ] Text files

---

# CORE-009 — Virtual File System (VFS)

### Description

Introduce a mount-based virtual filesystem to decouple asset paths from physical locations.

Example

```text
assets://textures/rocket.png

engine://shaders/basic.glsl

user://saves/save01.json
```

### Requirements

Support

* Mount points
* Relative paths
* Asset lookup
* Search order

### Future

* ZIP archives
* PAK files
* Network assets

### Acceptance Criteria

* [ ] Mount API
* [ ] Resolve virtual paths
* [ ] Integrates with File System API

---

# CORE-010 — Memory Allocation System

### Description

Centralize memory management and prepare for future profiling and optimization.

### Allocators

* Linear allocator
* Stack allocator
* Pool allocator
* Free list allocator
* Arena allocator

### Features

* Allocation tracking
* Leak detection
* Memory statistics
* Debug labels

### Acceptance Criteria

* [ ] Base allocator interface
* [ ] At least one custom allocator implemented
* [ ] Allocation statistics available
* [ ] Leak report on shutdown

---

# CORE-011 — Job System

**Priority**

Medium (defer until the engine has enough systems to benefit from it)

### Description

Implement a lightweight task scheduler to execute independent work in parallel.

### Candidate Jobs

* Physics update
* Animation update
* Visibility culling
* Asset loading
* AI
* Audio mixing

### Requirements

* Worker thread pool
* Work-stealing queue (optional)
* Futures/promises or job handles
* Dependency support
* Graceful shutdown

### Acceptance Criteria

* [ ] Thread pool starts with configurable worker count
* [ ] Jobs can be queued from any thread
* [ ] Wait for individual jobs or all jobs
* [ ] Clean shutdown without leaked threads
* [ ] Example: parallel execution of multiple dummy jobs

---
