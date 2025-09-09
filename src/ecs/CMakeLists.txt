set(LIBRARY_NAME ecs)

add_library(${LIBRARY_NAME} STATIC
    app.cpp
    input.cpp
    schedule.cpp
    window.cpp
)

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIBRARY_NAME} PRIVATE SDL3::SDL3)
