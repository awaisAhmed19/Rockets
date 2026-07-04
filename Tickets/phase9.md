```text
Sound File
      ↓
Asset Manager
      ↓
Audio Buffer
      ↓
Audio Source
      ↓
Mixer
      ↓
Effects
      ↓
Spatialization
      ↓
Output Device
```


---

# EPIC — Audio Device

---

# AUDIO-001 — Audio Backend

**Priority:** Critical

### Description

Initialize the engine's audio backend (SDL3 Audio initially).

### Responsibilities

* Device enumeration
* Open audio device
* Configure sample rate
* Configure channels
* Shutdown

### Tasks

* [ ] Initialize SDL Audio
* [ ] Enumerate Devices
* [ ] Open Default Device
* [ ] Open Specific Device
* [ ] Close Device
* [ ] Error Handling

### Acceptance Criteria

* [ ] Audio device opens
* [ ] Device information available
* [ ] Graceful shutdown

---

# AUDIO-002 — Audio Format

### Description

Support common PCM formats used internally by the engine.

### Formats

* [ ] Mono
* [ ] Stereo
* [ ] 16-bit PCM
* [ ] 32-bit Float

### Acceptance Criteria

* [ ] Internal conversion
* [ ] Format validation

---

# EPIC — Audio Resources

---

# AUDIO-100 — Audio Buffer

### Description

Store decoded audio data in memory.

### Tasks

* [ ] PCM storage
* [ ] Sample count
* [ ] Duration
* [ ] Sample rate
* [ ] Channel count

### Acceptance Criteria

* [ ] Immutable after loading
* [ ] Shared between sources

---

# AUDIO-101 — Audio Loader

### Description

Load audio assets from disk.

### Formats

* [ ] WAV
* [ ] OGG
* [ ] MP3
* [ ] FLAC

### Future

* [ ] Opus

### Acceptance Criteria

* [ ] Decode correctly
* [ ] Metadata available

---

# EPIC — Audio Sources

---

# AUDIO-200 — Audio Source

### Description

Represent a sound instance in the world.

### API

```cpp
AudioSource source;

source.Play();

source.Stop();

source.Pause();
```

### Properties

* Volume
* Pitch
* Looping
* Mute
* Priority

### Acceptance Criteria

* [ ] Play
* [ ] Pause
* [ ] Resume
* [ ] Stop
* [ ] Looping

---

# AUDIO-201 — Playback Control

### Tasks

* [ ] Seek
* [ ] Playback position
* [ ] Playback speed
* [ ] Fade In
* [ ] Fade Out

---

# EPIC — Listener

---

# AUDIO-300 — Audio Listener

### Description

Represent the "ears" of the player.

### Properties

* Position
* Orientation
* Velocity

### Features

* 3D attenuation
* Doppler effect
* Distance model

### Acceptance Criteria

* [ ] Single listener
* [ ] Camera synchronization
* [ ] Distance attenuation

---

# AUDIO-301 — Spatial Audio

### Tasks

* [ ] Stereo panning
* [ ] Distance attenuation
* [ ] Doppler
* [ ] Cone attenuation

### Future

* [ ] HRTF

---

# EPIC — Mixer

---

# AUDIO-400 — Mixer

### Description

Mix all active audio sources into one output stream.

### Responsibilities

* Mix channels
* Volume control
* Prevent clipping

### Tasks

* [ ] Source mixing
* [ ] Master volume
* [ ] Clipping prevention

---

# AUDIO-401 — Audio Buses

### Buses

```text
Master

Music

SFX

UI

Voice

Ambient
```

### Acceptance Criteria

* [ ] Independent volume
* [ ] Mute
* [ ] Solo

---

# EPIC — Streaming

---

# AUDIO-500 — Audio Streaming

### Description

Support large audio files without loading them entirely into memory.

### Use Cases

* Background music
* Ambient tracks
* Long dialogue

### Tasks

* [ ] Stream from disk
* [ ] Ring buffer
* [ ] Background thread
* [ ] Seamless looping

### Acceptance Criteria

* [ ] Low memory usage
* [ ] No playback gaps

---

# EPIC — Audio Effects

---

# AUDIO-600 — DSP Effects

### Tasks

* [ ] Gain
* [ ] Low-pass filter
* [ ] High-pass filter
* [ ] Reverb
* [ ] Echo
* [ ] Compressor

### Future

* [ ] EQ
* [ ] Chorus
* [ ] Distortion

---

# AUDIO-601 — Environmental Audio

### Tasks

* [ ] Reverb zones
* [ ] Occlusion
* [ ] Obstruction
* [ ] Room simulation

---

# EPIC — Debugging

---

# AUDIO-700 — Audio Debug Tools

### Features

* Active sources
* Playing sounds
* Bus volumes
* Voice count
* CPU usage

---

# AUDIO-701 — Audio Profiler

### Statistics

* Active voices
* Streaming buffers
* Mixing time
* Memory usage

---

# Recommended implementation order

```text
AUDIO-001  Audio Backend
        ↓
AUDIO-002  Audio Format
        ↓
AUDIO-100  Audio Buffer
AUDIO-101  Audio Loader
        ↓
AUDIO-200  Audio Source
AUDIO-201  Playback Control
        ↓
AUDIO-400  Mixer
AUDIO-401  Audio Buses
        ↓
AUDIO-300  Listener
AUDIO-301  Spatial Audio
        ↓
AUDIO-500  Streaming
        ↓
AUDIO-600  DSP Effects
        ↓
AUDIO-700  Debug Tools
```

---

## One thing I'd change architecturally

For a modern engine, I would **separate the audio backend from the audio engine**, much like you separated the renderer from OpenGL.

```text
Audio/
├── Core/
│   ├── AudioEngine
│   ├── Mixer
│   ├── Bus
│   ├── Source
│   ├── Listener
│   └── DSP/
│
├── Resources/
│   ├── AudioBuffer
│   ├── AudioClip
│   └── StreamingClip
│
├── Backend/
│   ├── SDLAudioBackend
│   ├── MiniAudioBackend (future)
│   └── OpenALBackend (future)
│
└── Debug/
```

