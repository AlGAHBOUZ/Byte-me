//
// Created by Ayman on 12/29/2022.
//

#ifndef HELLOSFML_GAME_H
#define HELLOSFML_GAME_H

#include "Card.h"
#include "Button.h"
#include <string>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

#define NUMBER_OF_CARDS 52

#define NUMBER_OF_VECTORS 7
#define NUMBER_OF_FINAL_STACKS 4

// NOTE: Stick to the naming conventions:
// Functions: Camel Case
// Variables: Underscores
// The name should be representative


class Game {
private:
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
    bool hint_pressed;

    // Undo Button variables
    Button *undo_btn;
    sf::RectangleShape undo_shape;
    sf::Texture undo_texture;
    bool undo_pressed;
    std::stringstream undo_string;
    sf::Text undotext;
    bool was_hidden;
    // Undo stack
    std::stack<std::string> undo;

    // Other Variables
    bool is_window_on_start_frame;

    // Timer variables
    sf::Clock clock;
    sf::Text timetext;
    sf::Time time;
    sf::Time time_start_btn;
    sf::Font font;
    std::stringstream ss;
    int seconds;
    int hours;
    int minutes;

    // score variables
    std::stringstream ss2;
    sf::Text score;
    int sco;

    // Drag Variables
    bool hover;
    bool dragable;
    bool picked_up;
    bool last_card_dragged;
    bool multiple_cards_dragged;
    Card* selected_card;
    int selected_card_i;
    int selected_card_j;

    // Private Functions
    void InitWindow();
    void InitStartBtn();
    void InitHintBtn();
    void InitUndoBtn();
    void InitCards();
    void UpdateBackgroundImage();
    void ShuffleCards();
    void DistributeCards();

public:
    // Constructor
    Game();

    // Destructor
    ~Game();

    // Functions
    bool IsRunning();
    void PollEvents();
    bool MouseIntersects(Card * card);


    // Drag and Drop functions
    void DragDrop();
    void selectCard();
    //Drag Functions
    bool DragLastCardFromVectors();
    bool DragLastCardToVectors(std::string previous_location);
    // Getters
    Card* get_selected_card();
    // Setters
    void set_picked_up(bool a);
    void set_selected_card_toNull();


    // Click function
    void MouseClick();

    // Winning function
    bool CheckWinStatus();

    // Hint button function
    bool Hint();

    // Undo button function
    bool Undo();

    // Move From functions
    void MoveFromDrawCardsStack();
    void MoveFromFlippedCardsStack();
    void MoveLastCardFromVectors();
    void MoveMultipleCardsFromVectors();
    void MoveFromFinalCardsStack(Card *playing_card, std::string previous_location);

    // Move To functions
    bool MoveToFinalCardsStacks(Card *playing_card, std::string previous_location);
    bool MoveToVectorsCards(Card *playing_card, std::string previous_location);
    bool MoveMultipleCardsToVectors(int vec_idx, int card_idx, std::string previous_location);

    // Testing functions for hint option
    bool testMoveToFinalCardsStacks(Card *playing_card);
    bool testMoveToVectorsCards(Card *playing_card);

    // Draw to window functions
    void DrawFrame();
    void DrawWinFrame();
};

#endif //HELLOSFML_GAME_H

