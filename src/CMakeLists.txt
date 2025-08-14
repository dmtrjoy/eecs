set(LIBRARY_NAME misha_src)

add_library(${LIBRARY_NAME} STATIC .)

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIBRARY_NAME} PRIVATE SDL3::SDL3)
