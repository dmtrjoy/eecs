enable_testing()

set(GTEST_VERSION 1.17.0)

include(FetchContent)
FetchContent_Declare(
  googletest
    URL https://github.com/google/googletest/archive/refs/tags/v${GTEST_VERSION}.tar.gz
    FIND_PACKAGE_ARGS ${GTEST_VERSION}
)

FetchContent_MakeAvailable(googletest)
