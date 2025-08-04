cmake_minimum_required(VERSION 3.10)

project(Win32MacroApp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES
    src/main.cpp
    src/macro/macro_manager.cpp
    src/input/mouse.cpp
    src/input/keyboard.cpp
    src/scripts/script_runner.cpp
)

add_executable(Win32MacroApp ${SOURCES})
set_target_properties(Win32MacroApp PROPERTIES WIN32_EXECUTABLE TRUE)