
## Suggested implementation order

I would **not** implement these in numerical order. Instead, build the minimum path that gets pixels on the screen and input flowing:

1. **PLAT-001** – SDL initialization
2. **PLAT-002** – Window management
3. **PLAT-009** – High Resolution Clock
4. **PLAT-008** – Timer API
5. **EVENT-001** – Event base system
6. **EVENT-002** → **EVENT-004** – Keyboard, Mouse, Window events
7. **EVENT-006** – Event dispatcher
8. **INPUT-001** – Keyboard input
9. **INPUT-002** – Mouse input
10. **PLAT-003** to **PLAT-007** – Quality-of-life platform features
11. **INPUT-003** – Controller support
12. **INPUT-004** – Action mapping

That sequence gets this to a functional engine much sooner, while leaving the more specialized platform features (file dialogs, clipboard, drag-and-drop, gamepads) until after the core loop is working.

* **PLAT** → OS abstraction (SDL)
* **EVENT** → Messaging
* **INPUT** → User input

---

# EPIC 1 — Platform Layer

---

# PLAT-001 — SDL Platform Initialization

**Type**

Feature

**Priority**

Critical

**Estimate**

2-4 hours

### Description

Initialize and shutdown the SDL subsystem. This is the engine's entry point into the operating system and should encapsulate all SDL initialization logic.

### Responsibilities

* Initialize SDL
* Initialize required SDL subsystems
* Shutdown SDL
* Error reporting

### Requirements

* Video subsystem
* Events subsystem
* Gamepad subsystem
* Timer subsystem

### Acceptance Criteria

* [ ] SDL initializes successfully
* [ ] Initialization failures are reported
* [ ] Shutdown cleans up all resources
* [ ] No SDL initialization code exists outside Platform module

---

# PLAT-002 — Window Management

**Priority**

Critical

### Description

Implement a platform-independent window abstraction.

### API

```cpp
Window window;

window.Create();

window.Show();

window.Hide();

window.Resize();

window.SetTitle();

window.Close();
```

### Features

* Create
* Destroy
* Resize
* Fullscreen
* Borderless
* VSync
* Minimize
* Maximize
* Focus

### Acceptance Criteria

* [ ] Window creation
* [ ] Resize
* [ ] Fullscreen toggle
* [ ] Title updates
* [ ] Window close event
* [ ] Multiple windows supported (future-ready)

---

# PLAT-003 — Monitor Management

### Description

Provide information about available displays.

### API

```cpp
Monitor::Count()

Monitor::Primary()

Monitor::Resolution()

Monitor::RefreshRate()

Monitor::DPI()
```

### Features

* Enumerate monitors
* Primary monitor
* Resolution
* Refresh rate
* DPI scaling
* Position

### Acceptance Criteria

* [ ] Detect monitors
* [ ] Detect refresh rates
* [ ] DPI retrieval
* [ ] Primary monitor detection

---

# PLAT-004 — Cursor Management

### Description

Provide complete cursor control.

### Features

* Show
* Hide
* Lock
* Unlock
* Relative mouse mode
* Cursor icons
* Custom cursor

### Acceptance Criteria

* [ ] Cursor visibility
* [ ] Relative mode
* [ ] Cursor locking
* [ ] Custom cursor loading

---

# PLAT-005 — Clipboard API

### Description

Expose clipboard functionality through the platform layer.

### API

```cpp
Clipboard::GetText()

Clipboard::SetText()
```

### Acceptance Criteria

* [ ] Copy text
* [ ] Paste text
* [ ] UTF-8 support

---

# PLAT-006 — Drag & Drop

### Description

Support native OS drag-and-drop events.

### Supported Payloads

* Files
* Directories
* Text

### Acceptance Criteria

* [ ] File drop events
* [ ] Multiple files
* [ ] Directory support

---

# PLAT-007 — Native File Dialogs

### Description

Provide cross-platform file dialogs.

### Features

* Open file
* Save file
* Pick directory
* File filters
* Multiple selection

### Acceptance Criteria

* [ ] Open dialog
* [ ] Save dialog
* [ ] Directory picker
* [ ] Extension filters

---

# PLAT-008 — Timer API

### Description

Provide high-level timing utilities.

### Features

* Stopwatch
* Delta timer
* Elapsed timer
* Countdown timer

### Acceptance Criteria

* [ ] Millisecond precision
* [ ] Pause/resume
* [ ] Reset support

---

# PLAT-009 — High Resolution Clock

### Description

Provide a high precision clock suitable for frame timing and profiling.

### API

```cpp
Clock::Now()

Clock::Delta()

Clock::Frequency()
```

### Requirements

* Nanosecond precision where supported
* Monotonic clock
* Cross-platform

### Acceptance Criteria

* [ ] Monotonic
* [ ] Stable timing
* [ ] Independent of system clock changes

---

# EPIC 2 — Event System

---

# EVENT-001 — Event Base System

### Description

Create the foundation of the engine's event architecture.

### Features

* Event interface
* Event categories
* Event types
* Timestamp
* Handled flag

### Acceptance Criteria

* [ ] Base Event class
* [ ] EventType enum
* [ ] EventCategory flags
* [ ] RTTI-free event identification

---

# EVENT-002 — Keyboard Events

### Events

```text
KeyPressed

KeyReleased

KeyRepeated

TextInput
```

### Acceptance Criteria

* [ ] Key code
* [ ] Modifier keys
* [ ] Repeat detection
* [ ] UTF-8 text input

---

# EVENT-003 — Mouse Events

### Events

```text
MouseMoved

MouseButtonPressed

MouseButtonReleased

MouseScrolled

MouseEntered

MouseLeft
```

### Acceptance Criteria

* [ ] Position
* [ ] Delta
* [ ] Scroll
* [ ] Button states

---

# EVENT-004 — Window Events

### Events

```text
WindowResize

WindowMove

WindowFocus

WindowLostFocus

WindowMinimize

WindowRestore

WindowClose
```

### Acceptance Criteria

* [ ] Resize
* [ ] Focus
* [ ] Close
* [ ] Minimize
* [ ] Restore

---

# EVENT-005 — Gamepad Events

### Events

```text
Connected

Disconnected

Button

Axis

Battery
```

### Acceptance Criteria

* [ ] Detect connect/disconnect
* [ ] Button input
* [ ] Analog sticks
* [ ] Triggers

---

# EVENT-006 — Event Dispatcher

### Description

Dispatch events to subscribers without tight coupling.

### Features

* Event queue
* Publish
* Subscribe
* Immediate dispatch
* Deferred dispatch

### Acceptance Criteria

* [ ] Type-safe dispatch
* [ ] Multiple listeners
* [ ] Event bubbling (future)
* [ ] Queue processing each frame

---

# EPIC 3 — Input

---

# INPUT-001 — Keyboard Input

### Description

Maintain current and previous keyboard state.

### API

```cpp
Input::IsKeyDown()

Input::IsKeyPressed()

Input::IsKeyReleased()
```

### Acceptance Criteria

* [ ] State tracking
* [ ] Press detection
* [ ] Release detection
* [ ] Repeat handling

---

# INPUT-002 — Mouse Input

### Features

* Position
* Delta
* Buttons
* Scroll
* Relative mode

### API

```cpp
Input::MousePosition()

Input::MouseDelta()

Input::IsMouseDown()
```

### Acceptance Criteria

* [ ] Position
* [ ] Delta
* [ ] Scroll
* [ ] Button states

---

# INPUT-003 — Controller Support

### Features

* Xbox
* PlayStation
* Generic SDL Gamepad
* Deadzones
* Vibration

### Acceptance Criteria

* [ ] Hot-plug support
* [ ] Analog sticks
* [ ] Triggers
* [ ] Haptic feedback

---

# INPUT-004 — Action Mapping

### Description

Decouple gameplay from physical input devices.

### Example

```ini
MoveForward = W
MoveForward = Gamepad_LeftStickUp

Jump = Space
Jump = Gamepad_A

Fire = Mouse_Left
Fire = RightTrigger
```

### Features

* Multiple bindings per action
* Runtime rebinding
* Save/load bindings
* Keyboard + controller support
* Axis mappings
* Composite bindings (future)

### Acceptance Criteria

* [ ] Register actions
* [ ] Query action state
* [ ] Rebind at runtime
* [ ] Serialize bindings
* [ ] Device-agnostic input queries

---

