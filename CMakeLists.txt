cmake_minimum_required(VERSION 3.20)

project(Helios VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(Engine)
add_subdirectory(Sandbox)

target_compile_options(Helios PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
)
target_compile_options(Sandbox PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
)