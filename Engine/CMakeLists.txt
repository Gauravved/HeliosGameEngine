add_library(Helios STATIC)

target_sources(Helios
    PRIVATE
        Source/Core/Application.cpp
        Source/Core/Log.cpp
        Source/Core/Layer.cpp 
        Source/Core/LayerStack.cpp

        Source/Platform/Windows/WindowsWindow.cpp
        Source/Platform/Windows/WindowsKeyMap.cpp
        Source/Platform/Windows/WindowsInput.cpp
        Source/Platform/Windows/WindowsPlatform.cpp

        Source/Renderer/RendererAPI.cpp
        Source/Renderer/RenderCommand.cpp
        Source/Renderer/Renderer.cpp
        Source/Renderer/Shader.cpp 

        Source/Renderer/Buffer/VertexBuffer.cpp
        Source/Renderer/Buffer/IndexBuffer.cpp 
        Source/Renderer/Buffer/VertexArray.cpp

        Source/Renderer/Camera/OrthographicCamera.cpp
        Source/Renderer/Camera/OrthographicCameraController.cpp
        Source/Renderer/Camera/PerspectiveCamera.cpp

        Source/Renderer/OpenGL/OpenGLContext.cpp
        Source/Renderer/OpenGL/OpenGLRendererAPI.cpp
        Source/Renderer/OpenGL/OpenGLVertexBuffer.cpp
        Source/Renderer/OpenGL/OpenGLIndexBuffer.cpp
        Source/Renderer/OpenGL/OpenGLVertexArray.cpp
        Source/Renderer/OpenGL/OpenGLShader.cpp

        Source/Input/Input.cpp 
        Source/Input/KeyCodes.cpp
        Source/Input/MouseButtonCodes.cpp

        ../ThirdParty/glad/src/gl.c 
        ../ThirdParty/glad/src/wgl.c
)

target_include_directories(Helios
    PUBLIC
        Include
        ../ThirdParty/glad/include
        ../ThirdParty/spdlog
        ../ThirdParty/glm
)
target_link_libraries(Helios
    PRIVATE
        opengl32
)