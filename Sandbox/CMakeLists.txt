add_executable(Sandbox
    Source/main.cpp
    Source/SandboxLayer.cpp 
)

target_include_directories(Sandbox
    PUBLIC 
        Include/ 
)

target_link_libraries(Sandbox
    PRIVATE
        Helios
)

add_custom_command(
    TARGET Sandbox POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Assets
        $<TARGET_FILE_DIR:Sandbox>/Assets
)