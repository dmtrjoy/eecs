cmake_minimum_required(VERSION 4.0.2)
project(
    eecs
    VERSION 0.0.1
    DESCRIPTION "A game engine"
    LANGUAGES CXX
)

option(BUILD_DOCS "Whether to build the documentation" OFF)
option(BUILD_EXAMPLES "Whether to build the examples" OFF)
option(BUILD_TESTS "Whether to build the tests" OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(thirdparty)
add_subdirectory(src)

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE ecs)

if(BUILD_DOCS)
    add_subdirectory(docs)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
