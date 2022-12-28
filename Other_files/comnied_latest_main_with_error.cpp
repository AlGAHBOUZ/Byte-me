#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <bits/stdc++.h>
#include "Card.h"
#include "Button.h"


void shuffle_array(Card * arr[], int n) {
    // To obtain a time-based seed
    // unsigned seed = 0;
    // another way of calculating the seed which makes different shuffle each time unlike the previous line
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();   // maybe it will need std::chrono // WE SHOULD TEST IT
    // Shuffling our array
    shuffle(arr, arr + n, std::default_random_engine(seed));
}

int main()
{
    // constant variable (number of all Card)
    const int NUMBER_OF_Card = 52;
    // array of pointers to Card
    Card * all_Card_arr[NUMBER_OF_Card] = {new Card(1, "spades"), new Card(2, "spades"),
                                              new Card(3, "spades"), new Card(4, "spades"),
                                              new Card(5, "spades"), new Card(6, "spades"),
                                              new Card(7, "spades"), new Card(8, "spades"),
                                              new Card(9, "spades"), new Card(10, "spades"),
                                              new Card(11, "spades"), new Card(12, "spades"),
                                              new Card(13, "spades"),
                                              new Card(1, "hearts"),new Card(2, "hearts"),
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
    shuffle_array(all_Card_arr, 4);
    // test
    for (int i = 0; i < 52; i++) {
        std::cout << all_Card_arr[i]->getNumber() << " ";
    }

    // 7 vectors of Card
    std::vector<Card*> Card_vectors_array[7];
    // Stack of the draw Card
    std::stack<Card*> draw_Card_stack;

    // moving the Card from the array to the draw stack
    for (int i = 0; i < 52; i++) {
        draw_Card_stack.push(all_Card_arr[i]);
    }
    // distributing the Card in the beginning of the game to the 7 vectors
    for(int vec = 0; vec < 7; vec++){
        for (int i = 0; i < vec + 1; i++) {
            Card_vectors_array[vec].push_back(draw_Card_stack.top());
            draw_Card_stack.pop();
        }
        // flipping the last card of each vector
        Card_vectors_array[vec][vec]->setHidden(0);
    }





// start of sfml

    sf::RenderWindow window(sf::VideoMode(1280,960),"Klondike",sf::Style::Titlebar | sf::Style::Close);
    sf::Texture BG;
    if (!BG.loadFromFile("img/pal.jpeg")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }

    float lastMouseX = 0;
    float lastMouseY = 0;

    sf::Sprite s(BG);
    s.setTextureRect(sf::IntRect (0,0,1280,960));
    s.setColor(sf::Color(255,255,255));

    sf::RectangleShape rec1;
    rec1.setSize(sf::Vector2f (120, 165));
    sf::Rect<float> sizeOfRec1 = rec1.getGlobalBounds();
    rec1.setOrigin( sf::Vector2f(sizeOfRec1.width/2, sizeOfRec1.height/2) );
    sf::Vector2f currPosition(1120,170);
    rec1.setPosition(currPosition);

    sf::Texture c1;
    if (!c1.loadFromFile("img/1hearts.png")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }
    rec1.setTexture(&c1);
/*
    sf::Texture texture;
    sf::Sprite playerImage;
    if (!texture.loadFromFile("img/d.png"))
    {
        return -1;
    }
    playerImage.setTexture(texture);
    playerImage.setScale(sf::Vector2f(0.5f, 0.5f));
    */
    sf::Font font;
    if (!font.loadFromFile("img/arial.ttf"))
    {
        return -1;
    }
    Button btn1("Start the Game!", {420, 100}, 42, sf::Color::Blue, sf::Color::Black);
    float z = window.getSize().y/2;
    float ab = window.getSize().x/3;
    btn1.setPosition({ab , z});
    btn1.setFont(font);




    sf::RectangleShape rec2;
    rec2.setSize({360, 100});
    rec2.setPosition({ab , z});

    sf::Texture c2;
    if (!c2.loadFromFile("img/stuff.png")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }
    rec2.setTexture(&c2);
/*
    std::string habd = "img/"+ std::to_string(1) + ".png";
    Card cardo(1, "hearts");


    cardo.setHidden(0);

    //must be after the path is set because it's where the path is read
    cardo.setPosition({1060, 85});



  some unused code for the old enter to start
    sf::Text text;
// select the font
    text.setFont(font); // font is a sf::Font
// set the string to display
    text.setString("Press Enter to start ;) ");
// set the character size
    text.setCharacterSize(42); // in pixels, not points!
// set the color
    text.setFillColor(sf::Color::White);
// set the text style
    text.setStyle(sf::Text::Bold);
    text.setPosition(220.f , window.getSize().y/2);
  */
    // test of card class
    // we need to set the size of the texture in the card class
    Card card(1, "hearts");
    card.setHidden(false);
    card.setPosition({200,150});

    bool f = window.isOpen();
    sf::Event event;
    while (window.isOpen())
    {
        // Test of card class





        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();


                case sf::Event::MouseMoved:
                    if(btn1.isMouseOver(window)){
                        btn1.setbackColor(sf::Color::White);
                    }
                    else{
                        btn1.setbackColor(sf::Color::Green);
                    }
                    break;
                case sf::Event::MouseButtonPressed:{
                    if(btn1.isMouseOver(window)){

                        f = 0;
                    }
                }

            }


        }
// here lies the enter button
        /* if(f){
             window.clear();
             window.draw(text);
             window.display();
         }
 */
        if(f){
            window.clear();
            window.draw(s);
            window.draw(rec2);
          // btn1.drawTo(window);
            window.display();
        }
        else{
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && rec1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                //std::cout << sf::Mouse::getPosition(window).x << " : " << sf::Mouse::getPosition(window).y << std::endl;
                rec1.setPosition(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
            }
            else{rec1.setPosition(currPosition);}

            window.clear();
            window.draw(s);
            window.draw(rec1);
            // testing card class
            card.drawTo(window);
            window.display();
        }

        /*
         if(event.type == sf::Event::KeyReleased){
             if(event.key.code == sf::Keyboard::Enter){
                 window.clear();
                 window.draw(playerImage);
                 window.display();
                 f = 0;
             }
         }
 */
    }
}
