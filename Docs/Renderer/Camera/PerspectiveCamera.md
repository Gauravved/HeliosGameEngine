# 🎬 3D Scene Rendering

Helios now supports rendering multiple 3D objects using a complete Model → View → Projection pipeline.

## 🔄 Model → View → Projection

Each object is defined in its own local coordinate space.

Before rendering, the object's Model matrix transforms it into world space:

```text
Local Space
    ↓
Model Matrix
    ↓
World Space
    ↓
View Matrix
    ↓
Camera Space
    ↓
Projection Matrix
    ↓
Clip / Screen Space
```

The vertex shader combines the object Model matrix with the camera View-Projection matrix:
```glsl
gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
```
This allows the same geometry to be rendered multiple times at different positions in the world.

## 🧊 Multiple Object Rendering

A single cube mesh can be reused to render multiple objects.

Each object receives its own Model matrix:
```cpp
for (const auto& position : cubePositions) {
    glm::mat4 model = glm::translate(
        glm::mat4(1.0f),
        position
    );

    m_Shader->SetMat4("u_Model", model);

    Helios::RenderCommand::DrawIndexed(m_VertexArray);
}
```
The geometry is stored only once:

```text
One Cube Mesh
     ↓
One VAO
One VBO
One IBO
     ↓
Multiple Model Matrices
     ↓
Multiple Objects
```

This allows multiple objects to share the same geometry while existing independently in world space.

## 🔍 Depth Testing

Helios uses OpenGL depth testing to ensure objects are rendered according to their distance from the camera.

```cpp
glEnable(GL_DEPTH_TEST);
```

Without depth testing, objects would be displayed based on draw order rather than their actual distance from the camera.

The depth buffer is cleared every frame:

```cpp
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

This ensures depth information from the previous frame does not affect the current frame.

## 🔺 Back-Face Culling

Helios uses back-face culling to avoid rendering triangles facing away from the camera.

```cpp
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);
glFrontFace(GL_CCW);
```

For closed objects such as cubes, roughly half of the triangles face away from the camera and do not need to be rendered.

This reduces unnecessary rendering work.

## 📏 Line Rendering

Helios supports rendering indexed geometry as lines.

The rendering flow follows the same abstraction used for triangle rendering:

```text
Sandbox
    ↓
RenderCommand::DrawLines()
    ↓
RendererAPI::DrawLines()
    ↓
OpenGLRendererAPI::DrawLines()
    ↓
GL_LINES
```

OpenGL interprets every pair of indices as one independent line:

0, 1 → Line
2, 3 → Line
4, 5 → Line

This functionality can be reused for:

Ground grids
Debug visualization
Object borders
Bounding boxes
World reference lines
Future editor tools and gizmos
🟦 XZ Ground Grid

A procedural ground grid is rendered using the line rendering system.

The grid exists on the:

XZ Plane

Y = 0

The grid is generated procedurally using two sets of lines:
```text
Lines parallel to Z
        +
Lines parallel to X
        ↓
      XZ Grid
```
Grid vertices and indices are generated dynamically, allowing the grid size and spacing to be adjusted easily.

The generated grid is uploaded to its own:

Vertex Array
Vertex Buffer
Index Buffer

and rendered using:

```cpp
Helios::RenderCommand::DrawLines(m_GridVertexArray);
```

The grid provides a spatial reference for navigating and testing the 3D scene.

## 📦 Current 3D Rendering Features

Perspective Camera        ✅
Mouse Look                ✅
Keyboard Movement         ✅
FOV Zoom                  ✅
Model Matrices            ✅
Multiple Object Rendering ✅
Depth Testing             ✅
Back-Face Culling         ✅
Line Rendering            ✅
XZ Ground Grid            ✅

## 🚀 Next Steps
```text
Reference / World Axes
        ↓
Cube Borders
        ↓
Complete 3D Test Environment
        ↓
ImGui Integration
        ↓
Editor Features
```