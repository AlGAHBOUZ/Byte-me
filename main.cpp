
#include "Game.h"

int main() {
    // Initializing the Solitaire game
    Game game;

    // Game loop
    while (game.IsRunning()) {
        // Events Loop
        game.PollEvents();

        // Drag and Drop
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
            game.selectCard();
            if (game.get_selected_card() != nullptr){
                game.DragDrop();
                game.set_picked_up(1);
            }
        }
        else{
            game.DragLastCardFromVectors();
            game.set_picked_up(0);
            game.set_selected_card_toNull();
        }

        // Check Winning Status
        if (game.CheckWinStatus()) {
            // Draw the winning frame
            game.DrawWinFrame();
        }
        else {
            // Draw
            game.DrawFrame();
        }
    }
}
