# Rendering Subsystem

Version: Phase 1
Status: Completed
Renderer: OpenGL 4.6
Graphics API Abstraction: Implemented

---

# Overview

The Rendering Subsystem is responsible for communicating with the underlying graphics API while exposing an engine-agnostic interface to the rest of Helios.

Current architecture:

Sandbox
      │
      ▼
RenderCommand
      │
      ▼
RendererAPI
      │
      ▼
OpenGLRendererAPI
      │
      ▼
OpenGL Driver
      │
      ▼
GPU

The rest of the engine never directly calls OpenGL functions.

---

# Goals

- Platform independent rendering interface
- Graphics API abstraction
- Easily replaceable backend
- Modern OpenGL implementation
- Future Vulkan support

---

# Current Features

## Window

✔ Win32 Window
✔ Message Loop
✔ Resize support

---

## OpenGL Context

Implemented:

- OpenGL 4.6 Core Profile
- GLAD Loader
- Context Creation
- Context Initialization
- Swap Buffers

Purpose:

Separates context creation from the Window implementation.

---

## RendererAPI

Purpose:

Abstract graphics API implementation.

Current Backend:

OpenGLRendererAPI

Future:

- VulkanRendererAPI
- DirectX12RendererAPI (optional)

Interface currently exposes:

- Init()
- SetViewport()
- SetClearColor()
- Clear()
- DrawIndexed()

---

## RenderCommand

Purpose:

Static facade over RendererAPI.

Architecture:

Sandbox
    │
    ▼
RenderCommand
    │
    ▼
RendererAPI
    │
    ▼
OpenGLRendererAPI

Advantages:

- Engine code never depends on OpenGL.
- Easy backend replacement.

---

## Buffers

### Vertex Buffer

Responsibilities:

- GPU vertex storage
- Upload vertex data
- Bind / Unbind

---

### Index Buffer

Responsibilities:

- GPU index storage
- Indexed rendering
- Stores index count

---

### Vertex Array

Responsibilities:

- Owns Vertex Buffers
- Owns Index Buffer
- Stores vertex attribute configuration

Current implementation automatically configures vertex attributes using BufferLayout.

---

## Buffer Layout

Purpose:

Describes memory layout of a vertex.

Example:

Position
Color

↓

Float3
Float3

↓

Stride
Offsets
Attribute count

Advantages:

Renderer code is completely generic.

---

## Shader System

Implemented:

- External shader loading
- Shader compilation
- Program linking
- Error reporting

Current shaders:

Vertex Shader

- Position
- Color

Fragment Shader

- RGB output

---

## Rendering Pipeline

Current pipeline:

Application
      │
      ▼
Layer
      │
      ▼
Renderer
      │
      ▼
RenderCommand
      │
      ▼
RendererAPI
      │
      ▼
OpenGLRendererAPI
      │
      ▼
OpenGL

---

## Layer System

Implemented:

Layer

LayerStack

Application owns LayerStack

Update loop:

Application
     │
     ▼
LayerStack
     │
     ▼
OnUpdate()

Purpose:

Allows multiple engine systems to update independently.

Future:

- ImGui Layer
- Editor Layer
- Runtime Layer

---

# Design Decisions

## Why RendererAPI?

To avoid engine code depending on OpenGL.

Changing graphics backend should not require changing gameplay code.

---

## Why RenderCommand?

Acts as a static façade.

Simplifies usage while hiding backend implementation.

---

## Why VertexArray owns Buffers?

Keeps rendering objects grouped together.

Matches modern OpenGL design.

---

## Why external shader files?

Advantages:

- Easy editing
- Better debugging
- Cleaner repository
- No recompilation after shader changes

---

# Current Limitations

Renderer currently supports:

✔ Triangles

Missing:

✖ Textures
✖ Uniform Buffers
✖ Framebuffers
✖ Cameras
✖ Mesh Import
✖ Materials
✖ Lighting
✖ Shadows
✖ PBR
✖ Instancing

---

# Future Optimizations

Rendering:

- Render Queue
- State Cache
- Command Buffer
- Batching
- Frustum Culling
- Instancing

API:

- Vulkan Backend
- Multithreaded Rendering
- Resource Manager

Shaders:

- Shader Reflection
- Include Support
- Hot Reloading

---

# Lessons Learned

Major concepts introduced:

- RAII
- Abstract Interfaces
- Static Factory Pattern
- Layered Architecture
- Graphics API Abstraction
- OpenGL Context Management
- GPU Buffers
- Vertex Specification
- Shader Compilation
- Indexed Rendering

---

# Current Result

Successfully renders an indexed RGB triangle using the Helios rendering pipeline.

Rendering flow:

Sandbox
   │
   ▼
Layer
   │
   ▼
RenderCommand
   │
   ▼
RendererAPI
   │
   ▼
OpenGLRendererAPI
   │
   ▼
GPU