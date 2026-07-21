add_library(Helios STATIC)

target_sources(Helios
    PRIVATE
        Source/Core/Application.cpp
        Source/Core/Log.cpp

        Source/Platform/Windows/WindowsWindow.cpp

        Source/Renderer/RendererAPI.cpp
        Source/Renderer/RenderCommand.cpp
        Source/Renderer/Renderer.cpp
        Source/Renderer/Shader.cpp 

        Source/Renderer/Buffer/VertexBuffer.cpp
        Source/Renderer/Buffer/IndexBuffer.cpp 
        Source/Renderer/Buffer/VertexArray.cpp

        Source/Renderer/OpenGL/OpenGLContext.cpp
        Source/Renderer/OpenGL/OpenGLRendererAPI.cpp
        Source/Renderer/OpenGL/OpenGLVertexBuffer.cpp
        Source/Renderer/OpenGL/OpenGLIndexBuffer.cpp
        Source/Renderer/OpenGL/OpenGLVertexArray.cpp
        Source/Renderer/OpenGL/OpenGLShader.cpp

        ../ThirdParty/glad/src/gl.c 
        ../ThirdParty/glad/src/wgl.c
)

target_include_directories(Helios
    PUBLIC
        Include
        ../ThirdParty/glad/include
        ../ThirdParty/spdlog
)
target_link_libraries(Helios
    PRIVATE
        opengl32
)