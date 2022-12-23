#pragma
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <bits/stdc++.h>
#include "Cards.h"
#include "Button.h"
using namespace sf;
using namespace std;

void shuffle_array(Cards * arr[], int n) {
    // To obtain a time-based seed
    unsigned seed = 0;
    // Shuffling our array
    shuffle(arr, arr + n, default_random_engine(seed));
}

int main()
{
    // constant variable (number of all cards)
    const int NUMBER_OF_CARDS = 52;
    // array of pointers to cards
    Cards * all_cards_arr[NUMBER_OF_CARDS] = {new Cards(1, "spades"), new Cards(2, "spades"),
                                              new Cards(3, "spades"), new Cards(4, "spades"),
                                              new Cards(5, "spades"), new Cards(6, "spades"),
                                              new Cards(7, "spades"), new Cards(8, "spades"),
                                              new Cards(9, "spades"), new Cards(10, "spades"),
                                              new Cards(11, "spades"), new Cards(12, "spades"),
                                              new Cards(13, "spades"),
                                              new Cards(1, "hearts"),new Cards(2, "hearts"),
                                              new Cards(3, "hearts"), new Cards(4, "hearts"),
                                              new Cards(5, "hearts"), new Cards(6, "hearts"),
                                              new Cards(7, "hearts"), new Cards(8, "hearts"),
                                              new Cards(9, "hearts"), new Cards(10, "hearts"),
                                              new Cards(11, "hearts"), new Cards(12, "hearts"),
                                              new Cards(13, "hearts"),
                                              new Cards(1, "diamond"), new Cards(2, "diamond"),
                                              new Cards(3, "diamond"), new Cards(4, "diamond"),
                                              new Cards(5, "diamond"), new Cards(6, "diamond"),
                                              new Cards(7, "diamond"), new Cards(8, "diamond"),
                                              new Cards(9, "diamond"), new Cards(10, "diamond"),
                                              new Cards(11, "diamond"), new Cards(12, "diamond"),
                                              new Cards(13, "diamond"),
                                              new Cards(1, "clover"), new Cards(2, "clover"),
                                              new Cards(3, "clover"), new Cards(4, "clover"),
                                              new Cards(5, "clover"), new Cards(6, "clover"),
                                              new Cards(7, "clover"), new Cards(8, "clover"),
                                              new Cards(9, "clover"), new Cards(10, "clover"),
                                              new Cards(11, "clover"), new Cards(12, "clover"),
                                              new Cards(13, "clover"),
    };

    // shuffle the cards
    shuffle_array(all_cards_arr, 4);
    // test
    for (int i = 0; i < 52; i++) {
        cout << all_cards_arr[i]->getNumber() << " ";
    }

    // 7 vectors of cards
    vector<Cards*> cards_vectors_array[7];
    // Stack of the draw cards
    stack<Cards*> draw_cards_stack;

    // moving the cards from the array to the draw stack
    for (int i = 0; i < 52; i++) {
        draw_cards_stack.push(all_cards_arr[i]);
    }
    // distributing the cards in the beginning of the game to the 7 vectors
    for(int vec = 0; vec < 7; vec++){
        for (int i = 0; i < vec + 1; i++) {
            cards_vectors_array[vec].push_back(draw_cards_stack.top());
            draw_cards_stack.pop();
        }
        // flipping the last card of each vector
        cards_vectors_array[vec][vec]->setHidden(0);
    }




    RenderWindow window;
    window.create(VideoMode(1280,800),"Klondike",Style::Default);

    Texture BG;
    if (!BG.loadFromFile("img/pal.jpg")) {
        cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }
    Sprite s(BG);
    s.setTextureRect(IntRect (0,0,1280,800));
    s.setColor(Color(255,255,255,64));
    RectangleShape rec1;
    rec1.setPosition(1060,85);
    rec1.setSize(Vector2f (120, 160));
    rec1.setOutlineColor(Color::White);

    Texture c1;
    if (!c1.loadFromFile("img/d.png")) {
        cout << "Load failed" << std::endl;
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

    string habd = "img/"+ to_string(1) + ".png";
    Cards cardo(3, "hearts");


    cardo.setHidden(0);

    //must be after the path is set because it's where the path is read
    cardo.setPosition({1060, 85});



/*     some unused code for the old enter to start
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

    bool f = window.isOpen();
    while (window.isOpen())
    {
        sf::Event event;

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
                        window.clear();
                        window.draw(s);
                        cardo.drawTo(window);
                        window.display();
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
           btn1.drawTo(window);
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