#include "game.hpp"
#include "raylib.h"

namespace engine {

void Game::initialize()
{
    InitWindow(800, 600, "My game");
    SetTargetFPS(60);
}

void Game::startup()
{
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RED);

        EndDrawing();
    }
}

void Game::shutdown()
{
    CloseWindow();
}

}
