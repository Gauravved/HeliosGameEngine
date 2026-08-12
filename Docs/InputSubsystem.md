# Input Subsystem

> Status: ✅ Completed

---

# Purpose

The Input Subsystem provides a platform-independent API for querying the current state of keyboard and mouse devices.

The rest of the engine interacts only with the abstract Input interface and never communicates directly with the operating system.

---

# Responsibilities

The subsystem currently supports:

- Keyboard state
- Mouse button state
- Mouse cursor position
- Left / Right modifier differentiation

---

# Architecture

```
Application
      │
      ▼
Input (Abstract Interface)
      ▲
      │
WindowsInput
      ▲
      │
Win32 API
```

---

# Why an Abstract Interface?

The engine should never depend on Windows APIs.

Instead it depends only on

```
Input
```

The platform layer decides which implementation should be instantiated.

Today:

```
WindowsInput
```

Future:

```
LinuxInput

MacInput
```

The rest of the engine remains unchanged.

---

# Singleton Ownership

The Input subsystem stores one active implementation.

Initialization is performed by

```
WindowsPlatform::Initialize()
```

which creates

```
WindowsInput
```

and registers it with the engine.

This ensures there is exactly one active platform input implementation.

---

# Keyboard Mapping

Windows virtual keys should never be exposed directly to engine code.

Instead they are translated into

```
Helios::KeyCode
```

using a lookup table.

```
Virtual Key

↓

WindowsKeyMap

↓

Engine KeyCode
```

Benefits:

- Platform independence
- Readable engine code
- Easy portability

---

# Left / Right Modifier Detection

Windows reports:

```
VK_SHIFT
VK_CONTROL
VK_MENU
```

These values are insufficient for distinguishing left and right keys.

The subsystem uses

- scan codes
- extended-bit information
- MapVirtualKeyW()

to correctly identify

- Left Shift
- Right Shift
- Left Ctrl
- Right Ctrl
- Left Alt
- Right Alt

---

# Mouse Position

Mouse coordinates are converted from

```
Screen Space

↓

Client Space
```

using

```
ScreenToClient()
```

This ensures all mouse coordinates are relative to the application window.

Coordinates outside the client area may become negative, which is expected behaviour.

---

# Keyboard State

Keyboard polling uses

```cpp
GetAsyncKeyState()
```

The high-order bit

```
0x8000
```

indicates whether a key is currently pressed.

Only the current key state is queried.

No input events are stored by the subsystem.

---

# Current Responsibilities

✅ Keyboard

✅ Mouse Buttons

✅ Mouse Position

✅ Platform Translation

---

# Advantages

- Platform-independent API
- Simple engine interface
- Easily extensible
- Supports multiple operating systems
- Clear ownership
- Fast key lookup

---

# Future Improvements

- Mouse Delta
- Mouse Capture
- Cursor Lock
- Cursor Visibility
- Raw Mouse Input
- Gamepad Support
- Input Contexts
- Action Mapping
- Event-backed Input Cache

---

# Lessons Learned

- The engine should expose engine-specific key codes rather than platform key codes.
- Translation should occur only inside the platform layer.
- The source of truth for input is the operating system.
- Platform-specific details such as scan codes and virtual keys remain hidden behind the Input interface.
- Correct left/right modifier detection requires more than virtual key codes.

## Milestone

This subsystem marks the completion of the engine's platform-independent input layer.

Subsystems depending on this:

- Camera Controller
- Editor Camera
- ImGui
- Gameplay Systems
- Scene System