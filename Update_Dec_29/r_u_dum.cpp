#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <bits/stdc++.h>
#include "Card.h"
#include "Button.h"
#define NUMBER_OF_Card 52
#define DRAW_STACK_X 155
#define DRAW_STACK_Y 165


void shuffle_array(Card * arr[], int n) {
    // To obtain a time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // Shuffling our array
    shuffle(arr, arr + n, std::default_random_engine(seed));
}

bool isMouseClickedCard(sf::Vector2<int> click_position){

}

int main() {
    // array of pointers to Cards
    Card *all_cards_array[NUMBER_OF_Card];
    // Initializing the 52 cards
    for (int num = 1; num <= 13; num++) {
        for (int i = 0; i < 4; i++) {
            std::string card_type;
            if (i == 0)
                card_type = "spades";
            else if (i == 1)
                card_type = "hearts";
            else if (i == 2)
                card_type = "diamond";
            else if (i == 3)
                card_type = "clover";
            all_cards_array[num - 1 + i * 13] = new Card(num, card_type);
        }
    }

    // shuffle the Cards
    shuffle_array(all_cards_array, NUMBER_OF_Card);

    // 7 vectors of Card
    std::vector<Card *> card_vectors_array[7];
    // Stack of the draw Card
    std::stack<Card *> draw_cards_stack;
    std::stack<Card *> drawn_flipped_cards_stack;
    // diamond - spades - hearts - clover
    std::stack<Card *> final_cards_stacks[4];

    // moving the Card from the array to the draw stack
    for (int i = 0; i < NUMBER_OF_Card; i++) {
        draw_cards_stack.push(all_cards_array[i]);
        //all_cards_array[i]->setPosition({155, 165});
    }

    // distributing the Card in the beginning of the game to the 7 vectors
    for (int vec = 0; vec < 7; vec++) {
        for (int i = 0; i < vec + 1; i++) {
            card_vectors_array[vec].push_back(draw_cards_stack.top());
            //int j = card_vectors_array[vec].size() - 1;
            //card_vectors_array[vec][j]->UpdatePosition(vec, j);
            draw_cards_stack.pop();
        }
        // flipping the last card of each vector
        card_vectors_array[vec][vec]->setHidden(0);
    }

    // start of sfml
    sf::RenderWindow window(sf::VideoMode(1280, 960), "Klondike", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(120);
    sf::Texture bg_texture;
    if (!bg_texture.loadFromFile("img/MS-BG-Empty.png")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }

    sf::Sprite bg_sprite(bg_texture);
    bg_sprite.setTextureRect(sf::IntRect(0, 0, 1280, 960));
    bg_sprite.setColor(sf::Color(255, 255, 255));

    // Start Button
    Button start_btn("Start the Game!", {312, 312}, 42, sf::Color::Blue, sf::Color::Black);
    float btn_x_pos = ((window.getSize().y / 2) + 70);
    float btn_y_pos = (window.getSize().x / 3) + 50;
    start_btn.setPosition({btn_y_pos, btn_x_pos});

    sf::RectangleShape btn_shape;
    btn_shape.setSize({312, 312});
    btn_shape.setPosition({btn_y_pos, btn_x_pos});

    sf::Texture btn_texture;
    if (!btn_texture.loadFromFile("img/start.png")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }
    btn_shape.setTexture(&btn_texture);

    bool is_window_open = window.isOpen();
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                // Event of clicking the close button of the window
                case sf::Event::Closed:
                    window.close();
                    break;
                    // Event of pressing Escape on the keyboard
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
                    // Event of clicking the mouse
                case sf::Event::MouseButtonPressed: {
                    // Clicking the start button in the beginning of the game
                    if (start_btn.isMouseOver(window)) {
                        is_window_open = 0;
                        break;
                    }
                    //bool mouse_click_flag = isMouseClickedCard(sf::Mouse::getPosition(window));
                    // Draw a new card when clicking on the deck stack
                    if (!draw_cards_stack.empty() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
                        draw_cards_stack.top()->getGlobalBounds().contains(
                                window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        Card *stored_card = draw_cards_stack.top();
                        stored_card->setHidden(0);
                        //stored_card->setPosition({DRAW_STACK_X + 165, DRAW_STACK_Y});
                        drawn_flipped_cards_stack.push(stored_card);
                        draw_cards_stack.pop();
                    }
                        // clicking a card in the drawn flipped cards stack
                    else if (!drawn_flipped_cards_stack.empty() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
                             drawn_flipped_cards_stack.top()->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        bool finale_stack_flag = 0;
                        Card *playing_card = drawn_flipped_cards_stack.top();
                        // checking if i can play in the finale cards stack
                        for (int i = 0; i < 4; i++) {
                            // if the card is an ace
                            if (final_cards_stacks[i].empty()) {
                                if (playing_card->getNumber() == 1) {
                                    if (i == 0 && playing_card->getSymbol() == "diamond") {
                                        final_cards_stacks[i].push(playing_card);
                                        drawn_flipped_cards_stack.pop();
                                        finale_stack_flag = 1;
                                        break;
                                    } else if (i == 1 && playing_card->getSymbol() == "spades") {
                                        final_cards_stacks[i].push(playing_card);
                                        drawn_flipped_cards_stack.pop();
                                        finale_stack_flag = 1;
                                        break;
                                    } else if (i == 2 && playing_card->getSymbol() == "hearts") {
                                        final_cards_stacks[i].push(playing_card);
                                        drawn_flipped_cards_stack.pop();
                                        finale_stack_flag = 1;
                                        break;
                                    } else if (i == 3 && playing_card->getSymbol() == "clover") {
                                        final_cards_stacks[i].push(playing_card);
                                        drawn_flipped_cards_stack.pop();
                                        finale_stack_flag = 1;
                                        break;
                                    }
                                }
                            } else if (final_cards_stacks[i].top()->getNumber() == playing_card->getNumber() - 1 &&
                                       final_cards_stacks[i].top()->getSymbol() == playing_card->getSymbol()) {
                                finale_stack_flag = 1;
                                final_cards_stacks[i].push(playing_card);
                                drawn_flipped_cards_stack.pop();
                                break;
                            }
                        }
                        if (!finale_stack_flag) {
                            // declaring an array to check if we can play in any possible vector
                            bool vector_flag_array_for_valid[7] = {0,0,0,0,0,0,0};
                            // looping on all vectors and comparing with the last element to check if we can play on it
                            for (int vec = 0; vec < 7; vec++) {
                                int sz = card_vectors_array[vec].size();
                                if(sz !=0){
                                    if (card_vectors_array[vec][sz - 1]->getNumber() == playing_card->getNumber() + 1 &&
                                        card_vectors_array[vec][sz - 1]->getColor() != playing_card->getColor()) {
                                        vector_flag_array_for_valid[vec] = 1;
                                        drawn_flipped_cards_stack.pop();
                                        card_vectors_array[vec].push_back(playing_card);
                                        break;
                                    }
                                }
                                else if(playing_card->getNumber() == 13){
                                    card_vectors_array[vec].push_back(playing_card);
                                    drawn_flipped_cards_stack.pop();
                                    vector_flag_array_for_valid[vec] = 1;
                                    break;
                                }

                            }
                        }
                    }


                    //start of the vectors part
                    for(int vec = 0; vec <7; vec++){
                        int vec_size = card_vectors_array[vec].size();

                        if(card_vectors_array[vec].size() != 0 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
                           card_vectors_array[vec][vec_size -1]->getGlobalBounds().contains(
                                   window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                            bool finale_stack_flag = 0;
                            Card *playing_card = card_vectors_array[vec][vec_size -1];
                            // checking if i can play in the finale cards stack
                            for (int i = 0; i < 4; i++) {
                                // if the card is an ace
                                if (final_cards_stacks[i].empty()) {
                                    if (playing_card->getNumber() == 1) {
                                        if (i == 0 && playing_card->getSymbol() == "diamond") {
                                            final_cards_stacks[i].push(playing_card);
                                            card_vectors_array[vec].pop_back();
                                            vec_size = card_vectors_array[vec].size();
                                            if(vec_size != 0){
                                                card_vectors_array[vec][vec_size-1]->setHidden(0);
                                            }
                                            finale_stack_flag = 1;
                                            break;
                                        } else if (i == 1 && playing_card->getSymbol() == "spades") {
                                            final_cards_stacks[i].push(playing_card);
                                            card_vectors_array[vec].pop_back();
                                            vec_size = card_vectors_array[vec].size();
                                            if(vec_size != 0){
                                                card_vectors_array[vec][vec_size-1]->setHidden(0);
                                            }
                                            finale_stack_flag = 1;
                                            break;
                                        } else if (i == 2 && playing_card->getSymbol() == "hearts") {
                                            final_cards_stacks[i].push(playing_card);
                                            card_vectors_array[vec].pop_back();
                                            vec_size = card_vectors_array[vec].size();
                                            if(vec_size != 0){
                                                card_vectors_array[vec][vec_size-1]->setHidden(0);
                                            }
                                            finale_stack_flag = 1;
                                            break;
                                        } else if (i == 3 && playing_card->getSymbol() == "clover") {
                                            final_cards_stacks[i].push(playing_card);
                                            card_vectors_array[vec].pop_back();
                                            vec_size = card_vectors_array[vec].size();
                                            if(vec_size != 0){
                                                card_vectors_array[vec][vec_size-1]->setHidden(0);
                                            }
                                            finale_stack_flag = 1;
                                            break;
                                        }
                                    }
                                } else if (final_cards_stacks[i].top()->getNumber() == playing_card->getNumber() - 1 &&
                                           final_cards_stacks[i].top()->getSymbol() == playing_card->getSymbol()) {
                                    finale_stack_flag = 1;
                                    final_cards_stacks[i].push(playing_card);
                                    card_vectors_array[vec].pop_back();
                                    vec_size = card_vectors_array[vec].size();
                                    if(vec_size != 0){
                                        card_vectors_array[vec][vec_size-1]->setHidden(0);
                                    }

                                    break;
                                }
                            }

                            if (!finale_stack_flag) {
                                // declaring an array to check if we can play in any possible vector
                                bool vector_flag_array_for_valid[7] = {0,0,0,0,0,0,0};
                                // looping on all vectors and comparing with the last element to check if we can play on it
                                for (int vecs = 0; vecs < 7; vecs++) {
                                    int sz = card_vectors_array[vecs].size();
                                    if(sz != 0){
                                        if (card_vectors_array[vecs][sz - 1]->getNumber() == playing_card->getNumber() + 1 &&
                                            card_vectors_array[vecs][sz - 1]->getColor() != playing_card->getColor()) {
                                            vector_flag_array_for_valid[vecs] = 1;
                                            card_vectors_array[vec].pop_back();
                                            vec_size = card_vectors_array[vec].size();
                                            if(vec_size != 0){
                                                card_vectors_array[vec][vec_size-1]->setHidden(0);
                                            }
                                            card_vectors_array[vecs].push_back(playing_card);
                                            break;
                                        }
                                    }
                                    else if(playing_card->getNumber() == 13){
                                        card_vectors_array[vecs].push_back(playing_card);
                                        card_vectors_array[vec].pop_back();
                                        vec_size = card_vectors_array[vec].size();
                                        std::cout << vec_size << std::endl;
                                        if(vec_size != 0){
                                            card_vectors_array[vec][vec_size-1]->setHidden(0);
                                        }
                                        vector_flag_array_for_valid[vecs] = 1;
                                        break;
                                    }

                                }
                            }
                        }
                    }
                }


            }
        }
        // Start button frame
        if (is_window_open) {
            window.clear();
            window.draw(bg_sprite);
            window.draw(btn_shape);
            window.display();
        } else {

            window.clear();
            window.draw(bg_sprite);

            // Draw the cards in the stacks
            if (!draw_cards_stack.empty()) {
                draw_cards_stack.top()->setPosition({DRAW_STACK_X, DRAW_STACK_Y});
                draw_cards_stack.top()->drawTo(window);
            }
            if (!drawn_flipped_cards_stack.empty()) {
                drawn_flipped_cards_stack.top()->setPosition({DRAW_STACK_X + 165, DRAW_STACK_Y});
                drawn_flipped_cards_stack.top()->drawTo(window);
            }
            // Draw the cards in the 4 final stacks
            for (int i = 0; i < 4; i++) {
                if (!final_cards_stacks[i].empty()) {
                    final_cards_stacks[i].top()->setPosition({static_cast<float>(DRAW_STACK_X + 3 * 165 + i * 165), DRAW_STACK_Y});
                    final_cards_stacks[i].top()->drawTo(window);
                }
            }

            // Draw the cards in the 7 vectors
            for (int vec = 0; vec < 7; vec++) {
                int sz = card_vectors_array[vec].size();
                for (int i = 0; i < sz; i++) {
                    card_vectors_array[vec][i]->UpdatePosition(vec, i);
                    card_vectors_array[vec][i]->drawTo(window);
//                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
//                        card_vectors_array[vec][i]->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&!card_vectors_array[vec][i]->getHidden()) {
//                        card_vectors_array[vec][i]->setPosition(
//                                sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
//                    }
//                         else{card_vectors_array[vec][i]->setPosition(card_vectors_array[vec][i]->getCurr());}
                }

            }

            window.display();
        }
    }
}
/* TO-DO:-
 * when clicking the draw stack if it's empty move all cards in the drawn_flipped_stack to the draw stack
        - Idea: maybe use a dummy card and initialize the draw cards stack with it
 * clicking the last card in the 7 vectors
 * clicking a group of cards in the 7 vectors
    Note: Only the king can move to an empty vector
 * */

/*
    // some new stuff
    // we could make two sets of flags for the same play in order to jump from one valid play to another?
    bool finale_stack_flag;
    Card * playing_card;
    // checking if i can play in the finale cards stack
    if(final_cards_stacks[1].top()->getNumber() == playing_card->getNumber() -1 && final_cards_stacks[1].top()->getSymbol() == playing_card->getSymbol() ){
        finale_stack_flag = 1;
    }
    // declaring an array to check if we can play in any possible vector
    bool vector_flag_array_for_valid[7];
    // looping on all vectors and comparing with the last element to check if we can play on it
    for (int vec = 0; vec < 7; vec++) {
        if(card_vectors_array[vec][vec]->getNumber() == playing_card->getNumber() -1 && card_vectors_array[vec][vec]->getColor() != playing_card->getColor()){
            vector_flag_array_for_valid[vec] = 1;
        }
    }

    if(finale_stack_flag){ // and you pressed that card of course
        final_cards_stacks[1].push(playing_card); // 1 will be changed with the index of the same stack of out card
    }
    else{ // or if finale_stack_flag but you pressed that card then if there is a valid move elsewhere the card will jump
        for (int vec = 0; vec < 7; vec++) {
            if(vector_flag_array_for_valid[vec]){
                card_vectors_array[vec].push_back(playing_card);
                break;
            }
        }
    }
*/
