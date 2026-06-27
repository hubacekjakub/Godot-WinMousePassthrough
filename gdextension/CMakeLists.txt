cmake_minimum_required(VERSION 3.22)
project(mouse_passthrough LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Match Godot's runtime on Windows — prevents CRT mismatch linker errors
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

# Pass -DGODOT_TARGET=template_release for release builds
set(GODOT_TARGET "template_debug" CACHE STRING
    "Godot export template target: template_debug or template_release")

# Suppress warnings from godot-cpp headers
set(GODOT_CPP_SYSTEM_HEADERS ON CACHE BOOL "" FORCE)
add_subdirectory(godot-cpp)

add_library(mouse_passthrough SHARED
    src/mouse_passthrough.cpp
    src/register_types.cpp
)

target_include_directories(mouse_passthrough PRIVATE src/)
target_link_libraries(mouse_passthrough PRIVATE godot-cpp)

set_target_properties(mouse_passthrough PROPERTIES
    PREFIX ""
    OUTPUT_NAME "mouse_passthrough.windows.${GODOT_TARGET}.x86_64"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../addons/windows_mouse_passthrough/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
)
