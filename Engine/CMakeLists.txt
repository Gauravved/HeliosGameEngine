add_library(Helios STATIC)

target_sources(Helios
    PRIVATE
        Source/Core/Application.cpp
        Source/Platform/Windows/WindowsWindow.cpp
)

target_include_directories(Helios
    PUBLIC
        Include
)