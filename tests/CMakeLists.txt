enable_testing()

file(GLOB_RECURSE TEST_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.t.cpp")

add_executable(tests ${TEST_FILES})

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set(GTEST_VERSION 1.17.0)
FetchContent_Declare(
  googletest
    URL https://github.com/google/googletest/archive/refs/tags/v${GTEST_VERSION}.tar.gz
    FIND_PACKAGE_ARGS ${GTEST_VERSION}
)

FetchContent_MakeAvailable(googletest)

target_link_libraries(tests PRIVATE SYSTEM
    gtest_main
    ${PROJECT_NAME})

include(GoogleTest)
gtest_discover_tests(tests)
