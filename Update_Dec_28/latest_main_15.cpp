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
    std::stack<Card *> final_cards_stacks[4];

    // moving the Card from the array to the draw stack
    for (int i = 0; i < NUMBER_OF_Card; i++) {
        draw_cards_stack.push(all_cards_array[i]);
        all_cards_array[i]->setPosition({155,165});
    }

    // distributing the Card in the beginning of the game to the 7 vectors
    for (int vec = 0; vec < 7; vec++) {
        for (int i = 0; i < vec + 1; i++) {
            card_vectors_array[vec].push_back(draw_cards_stack.top());
            int j = card_vectors_array[vec].size() - 1;
            card_vectors_array[vec][j]->UpdatePosition(vec, j);
            draw_cards_stack.pop();
        }
        // flipping the last card of each vector
        card_vectors_array[vec][vec]->setHidden(0);
    }

    // start of sfml
    sf::RenderWindow window(sf::VideoMode(1280, 960), "Klondike", sf::Style::Titlebar | sf::Style::Close);
//    window.setFramerateLimit(60);
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
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed: {
                    if (start_btn.isMouseOver(window)) {
                        is_window_open = 0;
                    }
                    break;
                }
            }
        }

        if (is_window_open) {
            window.clear();
            window.draw(bg_sprite);
            window.draw(btn_shape);
            window.display();
        } else {

            window.clear();
            window.draw(bg_sprite);

            // Draw the cards in the stacks
            if (!draw_cards_stack.empty())
                draw_cards_stack.top()->drawTo(window);

            if (!drawn_flipped_cards_stack.empty())
                drawn_flipped_cards_stack.top()->drawTo(window);
            for (int i=0; i<4; i++){
                if (!final_cards_stacks[i].empty())
                    final_cards_stacks[i].top()->drawTo(window);
            }
            // the same code will be written for the other 5 stacks

            // Draw the cards in the 7 vectors
            for (int vec = 0; vec < 7; vec++){
                int sz = card_vectors_array[vec].size();
                for (int i = 0; i < sz; i++) {
                    card_vectors_array[vec][i]->drawTo(window);
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && card_vectors_array[vec][i]->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && !card_vectors_array[vec][i]->getHidden()){
                        card_vectors_array[vec][i]->setPosition(sf::Vector2f (sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y));
                    }
                    // else{card_vectors_array[vec][i]->setPosition(card_vectors_array[vec][i]->getCurr());}
                }

            }

            // Draw a new card when clicking on the deck stack
            // IT SHOULD BE AN EVENT NOT A REALTIME FUNCTION
            if (!draw_cards_stack.empty() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && draw_cards_stack.top()->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                Card * stored_card = draw_cards_stack.top();
                stored_card->setHidden(0);
                stored_card->setPosition({DRAW_STACK_X + 165,DRAW_STACK_Y});
                drawn_flipped_cards_stack.push(stored_card);
                draw_cards_stack.pop();
            }

            window.display();
        }
    }
}
