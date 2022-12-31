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


// WARNING: Do NOT CHANGE any name in this file
// @ M_K,  @ sajed


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

    // Containers
    // Array of pointers to Cards
    Card *all_cards_array[NUMBER_OF_CARDS];
    // 7 vectors of Cards
    std::vector<Card *> card_vectors_array[7];
    // Stack of the draw Cards
    std::stack<Card *> draw_cards_stack;
    std::stack<Card *> drawn_flipped_cards_stack;
    // The 4 final stacks
    // Order: diamond - spades - hearts - clover
    std::stack<Card *> final_cards_stacks[4];

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
    int sco=0;

    // string for hints
    std::string hint = " ";
    std::stringstream hinto;
    sf::Text hinttext;
    bool hint_pressed = 0;

    // Private Functions
    void InitWindow(); // added the function that lods the button here too
    void InitStartBtn();
    void HintBtn(); // new function to draw the button here
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
    bool Hint(); // habd
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
    
    // new functions to help in hint (same as the above but they don't push)
    bool testMoveToFinalCardsStacks(Card *playing_card);
    bool testMoveToVectorsCards(Card *playing_card);
    
    // Draw to window functions
    void DrawFrame(); // and added some stuff in here too
    void DrawWinFrame();
};

#endif //HELLOSFML_GAME_H

