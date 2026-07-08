add_library(Helios STATIC)

target_sources(Helios
    PRIVATE
        Source/Core/Application.cpp
        Source/Platform/Windows/WindowsWindow.cpp
 "Include/Helios/Renderer/GraphicsContext.h" "Include/Helios/Renderer/OpenGLContext.h" "Include/Helios/Renderer/RendererAPI.h" "Source/Renderer/OpenGLContext.cpp")

target_include_directories(Helios
    PUBLIC
        Include
)