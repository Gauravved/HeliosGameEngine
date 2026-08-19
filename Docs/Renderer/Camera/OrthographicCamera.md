# Helios - Orthographic Camera Subsystem

The Orthographic Camera subsystem provides the Helios engine with a camera optimized for 2D rendering and editor-style views. Unlike a perspective camera, this implementation does not apply perspective scaling—objects maintain their apparent size regardless of their distance from the camera.

## 📂 Folder Structure

Camera functionality conceptually belongs to the renderer, but implementations remain decoupled from the core rendering infrastructure. This ensures the engine can easily scale to support multiple camera types (e.g., Perspective).

```text
Engine/
├── Include/Helios/Renderer/Camera/
│   ├── Camera.h
│   ├── OrthographicCamera.h
│   └── OrthographicCameraController.h
└── Source/Renderer/Camera/
    ├── OrthographicCamera.cpp
    └── OrthographicCameraController.cpp
```

## 🏗️ Core Architecture

The subsystem is built on three primary components:

### 1. `Camera` (Base Abstraction)
The foundational camera class shared by all implementations. Its sole responsibility is storing and exposing the **Projection Matrix**. It remains agnostic to whether the projection is orthographic or perspective, keeping the renderer independent of specific camera math.

### 2. `OrthographicCamera`
Extends the base camera with spatial state, defining the camera's presence in the world. 
* **State maintained:** Position, Rotation (Z-axis).
* **Matrices maintained:** Projection, View, and the combined View-Projection.
* **Aspect Ratio:** The horizontal projection boundaries adapt to the viewport's aspect ratio, while vertical boundaries scale with zoom, ensuring geometry proportions remain intact without modifying mesh data.

### 3. `OrthographicCameraController`
Separates input and timing logic from the camera itself. It connects the `OrthographicCamera` to Helios' internal systems:
* **Frame-Rate Independent Movement:** Uses the `TimeStep` system (`Speed × Delta Time`).
* **Input Handling:** Queries the Helios Input abstraction rather than direct Win32 APIs.
* **Event System Integration:** Listens for `WindowResizeEvent` to dynamically update the aspect ratio.

## 🎮 Controls (Editor-Style)

The controller currently utilizes an editor-style movement scheme designed to avoid conflict with standard gameplay inputs:

* **Activate Movement:** Hold `Right Mouse Button (RMB)`
* **Pan Up:** `RMB` + `W`
* **Pan Down:** `RMB` + `S`
* **Pan Left:** `RMB` + `A`
* **Pan Right:** `RMB` + `D`
* 
* ## 🔍 Zoom

The orthographic camera implements zoom by modifying the size of its
projection boundaries rather than physically moving the camera.

The controller maintains:

```cpp
float m_ZoomLevel = 1.0f;
left   = -m_AspectRatio * m_ZoomLevel;
right  =  m_AspectRatio * m_ZoomLevel;
bottom = -m_ZoomLevel;
top    =  m_ZoomLevel;
```
Reducing m_ZoomLevel reduces the visible world-space region and therefore
makes objects appear larger.

Increasing m_ZoomLevel increases the visible world-space region and therefore
makes objects appear smaller.

Zoom Level ↓ → Smaller viewing region → Zoom In
Zoom Level ↑ → Larger viewing region → Zoom Out

Mouse wheel input is handled through MouseScrolledEvent and forwarded through
the LayerStack to the OrthographicCameraController.

Mouse Scroll
      ↓
Application
      ↓
LayerStack
      ↓
SandboxLayer
      ↓
OrthographicCameraController
      ↓
Update Zoom Level
      ↓
SetProjection()
      ↓
Updated Projection Matrix

A minimum zoom level is enforced to prevent the projection bounds from becoming
invalid.

## 🔄 Camera Rotation

The orthographic camera supports rotation around the Z-axis.

While RMB is held, horizontal mouse movement is converted into a mouse delta:

Current Mouse X - Previous Mouse X
             ↓
       Rotation Delta
             ↓
      Camera Rotation

The controller tracks the previous mouse position and initializes it when RMB camera control begins to prevent sudden rotation jumps.

The resulting rotation is passed to:
```cpp
m_Camera.SetRotation(rotation);
```

which causes the camera to recalculate its View and View-Projection matrices.

## ⚙️ Rendering Pipeline Integration

The camera fully integrates into the Helios rendering pipeline, acting as the owner of its transformation state. Matrix recalculations only occur when the camera's state changes.

```text
Input ➔ Camera Controller ➔ Camera State ➔ View-Projection Matrix ➔ Shader ➔ Rendered Geometry
```

### Event Flow

```text
Application ➔ LayerStack ➔ SandboxLayer ➔ OrthographicCameraController ➔ EventDispatcher
```

## ✅ Current Status

- [x] Base `Camera` abstraction
- [x] `OrthographicCamera` implementation (Position, Rotation, Matrices)
- [x] Aspect-ratio-aware projection
- [x] `OrthographicCameraController` abstraction
- [x] TimeStep-based, frame-rate independent movement (RMB + WASD)
- [x] Event handling & dynamic Window Resize support
- [x] Shader integration

## 🚀 Future Direction

This orthographic implementation establishes the baseline architecture for future 3D expansion. The planned roadmap includes:

1. **Perspective Camera:** Introducing Field of View (FOV), near/far clipping planes, and 3D spatial positioning.
2. **3D Camera Controller:** Supporting forward/right/up movement vectors and mouse-look controls.
3. **3D Rendering Pipeline:** Integrating Depth Testing and 3D Mesh Rendering.
4. **Editor Viewport:** Fully integrating the camera systems into the Helios visual editor.
