//
// Created by Ayman on 12/29/2022.
//

#ifndef HELLOSFML_GAME_H
#define HELLOSFML_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>
#include "Card.h"
#include "Button.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

#define NUMBER_OF_CARDS 52


// WARNING: Do NOT CHANGE any name in this file
// @ M_K,  @ sajed

class Game {
private:
    // Window
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Texture bg_texture;
    sf::Texture bg_texture_updated;
    sf::Sprite *bg_sprite;
    // Event
    sf::Event event;
    // Start Button
    Button *start_btn;
    sf::RectangleShape btn_shape;
    sf::Texture btn_texture;
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
    sf::Clock clock;
    sf::Text timetext;
    sf::Time time;
    sf::Font font;
    std::stringstream ss;
    int s=0;
    int g=0;
    int m=0;
    // Private Functions
    void InitWindow();
    void InitStartBtn();
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
    bool GetIsRunning();
    void PollEvents();
    void MouseClick();

    // Move From functions
    void MoveFromDrawCardsStack();
    void MoveFromFlippedCardsStack();
    void MoveFromVectorsCards();
    void MoveMultipleCards(Card *playing_card);
    bool win();
    bool loss();
    // Move To functions
    bool MoveToFinalCardsStacks(Card *playing_card);
    bool MoveToVectorsCards(Card *playing_card);
    // Draw to window function
    void DrawFrame();
    // TO-DO Functions
    // Bool CheckWin();


};


#endif //HELLOSFML_GAME_H
