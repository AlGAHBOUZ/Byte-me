//
// Created by Ayman on 12/29/2022.
//

#ifndef HELLOSFML_GAME_H
#define HELLOSFML_GAME_H

#include "Card.h"
#include "Button.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

#define NUMBER_OF_CARDS 52

#define NUMBER_OF_VECTORS 7
#define NUMBER_OF_FINAL_STACKS 4

// NOTE: Stick to the naming conventions:
// Functions: Camel Case
// Variables: Underscores
// The name should be representative
// WARNING: Do NOT CHANGE any name in this file


class Game {
private:
    // Window variables
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Texture bg_texture;
    sf::Texture bg_texture_updated;
    sf::Sprite *bg_sprite;

    // Event variable
    sf::Event event;

    // Start Button variables
    Button *start_btn;
    sf::RectangleShape btn_shape;
    sf::Texture btn_texture;

    // Hint Button variables
    Button *hint_btn;
    sf::RectangleShape hint_shape;
    sf::Texture hint_texture;
    // string for hints
    std::string hint = " ";
    std::stringstream hinto;
    sf::Text hinttext;
    bool hint_pressed = 0;

    // Containers
    // Array of pointers to Cards
    Card *all_cards_array[NUMBER_OF_CARDS];
    // 7 vectors of Cards
    std::vector<Card *> card_vectors_array[NUMBER_OF_VECTORS];
    // Stack of the draw Cards
    std::stack<Card *> draw_cards_stack;
    std::stack<Card *> drawn_flipped_cards_stack;
    // The 4 final stacks
    // Order: diamond - spades - hearts - clover
    std::stack<Card *> final_cards_stacks[NUMBER_OF_FINAL_STACKS];

    // Other Variables
    bool is_window_on_start_frame;

    // Timer variables
    sf::Clock clock;
    sf::Text timetext;
    sf::Time time;
    sf::Font font;
    std::stringstream ss;
    int seconds;
    int hours;
    int minutes;

    // score variables
    std::stringstream ss2;
    sf::Text score;
    int sco;

    // Private Functions
    void InitWindow();
    void InitStartBtn();
    void InitHintBtn();
    void InitCards();
    void UpdateBackgroundImage();
    void ShuffleCards();
    void DistributeCards();
public:
    // Constructors
    Game();

    // Destructor
    ~Game();

    // Functions
    bool IsRunning();
    void PollEvents();
    void DragDrop();
    void MouseClick();

    // Winning and losing functions
    bool CheckWinStatus();
    bool CheckLossStatus(); // NEEDS TESTING
    bool Hint();

    // Move From functions
    void MoveFromDrawCardsStack();
    void MoveFromFlippedCardsStack();
    void MoveLastCardFromVectors();
    void MoveMultipleCardsFromVectors();
    void MoveFromFinalCardsStack(Card *playing_card);

    // Move To functions
    bool MoveToFinalCardsStacks(Card *playing_card);
    bool MoveToVectorsCards(Card *playing_card);
    bool MoveMultipleCardsToVectors(int vec_idx, int card_idx);

    // Testing functions for hint option
    bool testMoveToFinalCardsStacks(Card *playing_card);
    bool testMoveToVectorsCards(Card *playing_card);

    // Draw to window functions
    void DrawFrame();
    void DrawWinFrame();
};

#endif //HELLOSFML_GAME_H

/*
 * How to calculate the score:
 * Any card moving to the final cards stack = 15
 * Any card moving from the flipped cards stack to the 7 vectors = 5
 * Any card moving from the 7 vectors to the 7 vectors (and a card is shown -> hidden = 0) = 5
 */

