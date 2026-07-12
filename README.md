# Rocket

> A modern C++20 game engine and application framework focused on clarity, performance, and educational value.

Rocket is a cross-platform engine written in modern C++ using SDL3 as its platform layer. The project emphasizes clean architecture, explicit ownership, lightweight abstractions, and an inspectable rendering pipeline rather than hiding complexity behind large frameworks.

The goal is not to compete with commercial engines, but to build a professional-quality codebase from first principles while remaining approachable for learning, experimentation, and future expansion.

---

## Philosophy

Rocket follows a few simple design principles.

- Modern C++20
- RAII everywhere
- Explicit ownership
- Minimal runtime allocations
- SDL-first platform layer
- Engine modules with clear responsibilities
- Educational over magical
- Performance-conscious without premature optimization

Instead of wrapping every SDL call behind unnecessary abstractions, Rocket embraces SDL where it provides value while exposing clean engine interfaces.

---

# Current Features

## Platform Layer

- SDL3 initialization
- Window creation and destruction
- Window management
- Resize handling
- Show / Hide
- Window title updates
- Fullscreen support
- Borderless mode
- Minimize / Maximize / Restore
- Focus management

---

## Event System

A lightweight event translation layer converts SDL events into engine events.

Supported events include:

- Keyboard
- Mouse movement
- Mouse buttons
- Mouse wheel
- Window resize
- Window focus
- Window close

---

## Input System

State-based input handling.

Keyboard

- Pressed
- Released
- Frame lifecycle
- Ready for justPressed / justReleased

Mouse

- Position
- Buttons
- Scroll delta
- Frame lifecycle

---

## Core

- High-resolution timer
- Logging
- Assertions
- Configuration parser
- Type aliases
- Utility helpers

---

## Math Library

Custom mathematics implementation.

Current modules include:

- Vector2
- Vector3
- Vector4
- Matrix2
- Matrix3
- Matrix4
- Quaternion
- Mathematical constants

The math library is implemented without external dependencies and is intended to support rendering, physics, cameras, animation, and editor tooling.

---

## Testing

The project contains dedicated math tests covering vectors and matrices.

---

# Project Structure

```
Rocket
├── src
│   ├── App
│   ├── Engine
│   │   ├── Core
│   │   ├── Event
│   │   ├── Input
│   │   ├── Math
│   │   ├── Platform
│   │   └── Tests
│   └── main.cpp
│
├── documentation
├── third_party
└── CMakeLists.txt
```

---

# Architecture

```
Application
      │
      ▼
Platform
      │
      ▼
Window
      │
      ▼
Event Dispatcher
      │
      ▼
Input System
      │
      ▼
Update
      │
      ▼
Renderer
```

Every subsystem has a single responsibility.

The application orchestrates the engine rather than implementing engine functionality itself.

---

# Build Requirements

- C++20 compiler
- CMake
- Ninja (recommended)
- SDL3
- SDL3_image
- SDL3_ttf
- OpenGL
- GLEW

Arch Linux packages

```
cmake
ninja
gcc
glew
sdl3
sdl3_image
sdl3_ttf
```

---

# Building

Clone the repository.

```bash
git clone <repository>
cd Rockets
```

Generate the project.

```bash
./bootstrap.sh
```

Build.

```bash
./build.sh
```

Or use CMake directly.

```bash
cmake -S . -B build/debug
cmake --build build/debug
```

---

# Design Goals

Rocket is being developed in layers.

Current development focuses on:

- Stable platform abstraction
- Input system
- Event pipeline
- Mathematics library
- Rendering foundation

Future milestones include:

- Renderer abstraction
- Asset management
- Camera system
- ECS
- Scene graph
- Resource manager
- Physics
- Audio
- UI framework
- Editor
- Vulkan backend

---

# Current Statistics

At the time of writing:

- **205 directories**
- **753 source files**
- Modular engine architecture
- Cross-platform SDL3 foundation
- Custom mathematics library
- Independent platform and input systems

---

# Coding Style

Rocket follows a consistent coding standard.

- C++20
- RAII ownership
- `m_` member naming
- `constexpr` where appropriate
- Header-only utilities when beneficial
- Minimal macros
- Assertions for programmer errors
- Clear separation between engine modules

---

# Dependencies

Third-party libraries are intentionally kept minimal.

- SDL3
- SDL3_image
- SDL3_ttf
- GLEW
- Dear ImGui

Everything else is implemented inside the engine.

---

# Roadmap

Phase 1

- Platform
- Window
- Events
- Input
- Core utilities

Phase 2

- Mathematics
- Camera
- Rendering API

Phase 3

- Assets
- Resource management
- Scene

Phase 4

- Editor
- Tools
- Runtime

---

# License

This project is currently under active development.

A license will be added before the first public release.

---

**Rocket** is built as both a learning platform and a long-term engine project, with an emphasis on clean architecture, modern C++, and understanding how game engines work from the ground up.
