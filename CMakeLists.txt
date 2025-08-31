cmake_minimum_required(VERSION 4.1.0)
project(
    eecs
    VERSION 0.0.1
    DESCRIPTION "A game engine"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(thirdparty)
add_subdirectory(src)
add_subdirectory(examples)

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE ecs)

add_subdirectory(tests)
