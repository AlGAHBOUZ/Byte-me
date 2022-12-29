#pragma once

#include "Game.h"

int main() {
    // Testing Class Game
    Game game;

    // Game loop
    while (game.GetIsRunning()) {
        // Update
        game.PollEvents();
        // Draw
        game.DrawFrame();
    }
}