add_library(Helios STATIC)

target_sources(Helios
    PRIVATE
        Source/Core/Application.cpp
        Source/Platform/Windows/WindowsWindow.cpp
        Source/Renderer/OpenGLContext.cpp
        Source/Renderer/OpenGLRendererAPI.cpp 
        Source/Renderer/RendererAPI.cpp
        Source/Renderer/RenderCommand.cpp
        Source/Renderer/Renderer.cpp

        ../ThirdParty/glad/src/gl.c 
        ../ThirdParty/glad/src/wgl.c 
 "Include/Helios/Core/Base.h")

target_include_directories(Helios
    PUBLIC
        Include
        ../ThirdParty/glad/include
)
target_link_libraries(Helios
    PRIVATE
        opengl32
)