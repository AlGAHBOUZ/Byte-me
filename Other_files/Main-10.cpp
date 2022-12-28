#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <bits/stdc++.h>
#include "Card.h"
#include "Button.h"
#define NUMBER_OF_Card 52


void shuffle_array(Card * arr[], int n) {
    // To obtain a time-based seed
    // unsigned seed = 0;
    // another way of calculating the seed which makes different shuffle each time unlike the previous line
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();   // maybe it will need std::chrono // WE SHOULD TEST IT
    // Shuffling our array
    shuffle(arr, arr + n, std::default_random_engine(seed));
}

int main() {
    // array of pointers to Card
    Card *all_Card_arr[NUMBER_OF_Card] = {new Card(1, "spades"), new Card(2, "spades"),
                                          new Card(3, "spades"), new Card(4, "spades"),
                                          new Card(5, "spades"), new Card(6, "spades"),
                                          new Card(7, "spades"), new Card(8, "spades"),
                                          new Card(9, "spades"), new Card(10, "spades"),
                                          new Card(11, "spades"), new Card(12, "spades"),
                                          new Card(13, "spades"),
                                          new Card(1, "hearts"), new Card(2, "hearts"),
                                          new Card(3, "hearts"), new Card(4, "hearts"),
                                          new Card(5, "hearts"), new Card(6, "hearts"),
                                          new Card(7, "hearts"), new Card(8, "hearts"),
                                          new Card(9, "hearts"), new Card(10, "hearts"),
                                          new Card(11, "hearts"), new Card(12, "hearts"),
                                          new Card(13, "hearts"),
                                          new Card(1, "diamond"), new Card(2, "diamond"),
                                          new Card(3, "diamond"), new Card(4, "diamond"),
                                          new Card(5, "diamond"), new Card(6, "diamond"),
                                          new Card(7, "diamond"), new Card(8, "diamond"),
                                          new Card(9, "diamond"), new Card(10, "diamond"),
                                          new Card(11, "diamond"), new Card(12, "diamond"),
                                          new Card(13, "diamond"),
                                          new Card(1, "clover"), new Card(2, "clover"),
                                          new Card(3, "clover"), new Card(4, "clover"),
                                          new Card(5, "clover"), new Card(6, "clover"),
                                          new Card(7, "clover"), new Card(8, "clover"),
                                          new Card(9, "clover"), new Card(10, "clover"),
                                          new Card(11, "clover"), new Card(12, "clover"),
                                          new Card(13, "clover"),
    };

    // shuffle the Card
    shuffle_array(all_Card_arr, NUMBER_OF_Card);
    // test
    for (int i = 0; i < NUMBER_OF_Card; i++) {
        std::cout << all_Card_arr[i]->getNumber() << " ";
    }

    // 7 vectors of Card
    std::vector<Card *> Card_vectors_array[7];
    // Stack of the draw Card
    std::stack<Card *> draw_Card_stack;

    // moving the Card from the array to the draw stack
    for (int i = 0; i < NUMBER_OF_Card; i++) {
        draw_Card_stack.push(all_Card_arr[i]);
        all_Card_arr[i]->setPosition({155,165});
    }
    // distributing the Card in the beginning of the game to the 7 vectors
    for (int vec = 0; vec < 7; vec++) {
        for (int i = 0; i < vec + 1; i++) {
            Card_vectors_array[vec].push_back(draw_Card_stack.top());
            int j = Card_vectors_array[vec].size() - 1;
            Card_vectors_array[vec][j]->UpdatePosition(vec, j);
            draw_Card_stack.pop();
        }
        // flipping the last card of each vector
        Card_vectors_array[vec][vec]->setHidden(0);
    }





// start of sfml

    sf::RenderWindow window(sf::VideoMode(1280, 960), "Klondike", sf::Style::Titlebar | sf::Style::Close);
    sf::Texture BG;
    if (!BG.loadFromFile("img/MS-BG.png")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }

    float lastMouseX = 0;
    float lastMouseY = 0;

    sf::Sprite s(BG);
    s.setTextureRect(sf::IntRect(0, 0, 1280, 960));
    s.setColor(sf::Color(255, 255, 255));

//    sf::RectangleShape rec1;
//    rec1.setSize(sf::Vector2f (120, 165));
//    sf::Rect<float> sizeOfRec1 = rec1.getGlobalBounds();
//    rec1.setOrigin( sf::Vector2f(sizeOfRec1.width/2, sizeOfRec1.height/2) );
//    sf::Vector2f currPosition(1120,170);
//    rec1.setPosition(currPosition);
//
//    sf::Texture c1;
//    if (!c1.loadFromFile("img/2hearts.png")) {
//        std::cout << "Load failed" << std::endl;
//        system("pause");
//        return -1;
//    }
//    rec1.setTexture(&c1);

    Button btn1("Start the Game!", {312, 312}, 42, sf::Color::Blue, sf::Color::Black);
    float ButtyPos = ((window.getSize().y/2)+70);
    float ButtxPos = (window.getSize().x / 3) + 50;
    btn1.setPosition({ButtxPos, ButtyPos});

    sf::RectangleShape rec2;
    rec2.setSize({312, 312});
    rec2.setPosition({ButtxPos, ButtyPos});

    sf::Texture c2;
    if (!c2.loadFromFile("img/start.png")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }
    rec2.setTexture(&c2);

    Card card(2, "hearts");
    card.setHidden(false);
    card.setPosition({200, 150});

    bool f = window.isOpen();
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();

                case sf::Event::MouseButtonPressed: {
                    if (btn1.isMouseOver(window)) {
                        f = 0;


                    }
                }

            }
        }

        if (f) {
            window.clear();
            window.draw(s);
            window.draw(rec2);
            window.display();
        } else {
//            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && rec1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
//                rec1.setPosition(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
//            }
//            else{rec1.setPosition(currPosition);

        window.clear();
        window.draw(s);
//        card.drawTo(window);
        if (!draw_Card_stack.empty())
            draw_Card_stack.top()->drawTo(window);
// the same code will be written for the other 5 stacks
        for (int vec = 0; vec < 7; vec++){
            int sz = Card_vectors_array[vec].size();
            for (int i = 0; i < sz; i++) {
                Card_vectors_array[vec][i]->drawTo(window);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && Card_vectors_array[vec][i]->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && !Card_vectors_array[vec][i]->getHidden()){
                    Card_vectors_array[vec][i]->setPosition(sf::Vector2f (sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y));
                }
//                else{Card_vectors_array[vec][i]->setPosition(Card_vectors_array[vec][i]->getCurr());}
            }
        }

        window.display();
    }
  }
}
