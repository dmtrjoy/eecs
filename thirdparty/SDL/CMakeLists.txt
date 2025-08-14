set(SDL_VERSION 3.2.20)

include(FetchContent)
FetchContent_Declare(
    SDL3
    URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-${SDL_VERSION}.tar.gz
)

FetchContent_MakeAvailable(SDL3)
