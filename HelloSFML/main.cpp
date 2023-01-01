
#include "Game.h"

int main() {
    // Initializing the Solitiare game
    Game game;

    // Game loop
    while (game.IsRunning()) {
        // Events Loop
        game.PollEvents();

        // Comment the next line to turn off drag & drop feature (which is buggy)
        //game.DragDrop();

        // Check Winning Status
        if (game.CheckWinStatus()) {
            // Draw the winning frame
            game.DrawWinFrame();
        }
        else {
            // Draw
            game.DrawFrame();
        }

        // Check Losing Status
//        if (game.CheckLossStatus()) {
//            // maybe another frame for losing (Loser hahaha!)
//            std::cout << "Good For You! YOU ARE A LOSER HAHAHAHA.\n";
//            break;
//        }
    }
}

// Testing clion with git