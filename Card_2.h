//
// Created by Dell on 12/25/2022.
//

#ifndef HELLOSFML_CARD_H
#define HELLOSFML_CARD_H


#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <bits/stdc++.h>

//using namespace sf;
//using namespace std;

class Card{
private:
    int number;
    bool hidden;
    std::string path ,path_hidden, path_not_hidden;
    enum symbol {
        clover,
        diamond,
        hearts,
        spades
    } card_symb;
    enum color {
        red,
        black,
    } card_clr;
    sf::Sprite card_sprite; // rectangle shape maybe replaced with sprite
    sf::Texture card_texture;
public:
    // Contructors
    Card();
    Card(int num, std::string symb);
    // Setters
    void setNumber(int num);
    void setHidden(bool h);
    void setSymbolClr(std::string symb);
    void setPosition(sf::Vector2f pos);

    // Getters
    const int getNumber() ;
    const int getHidden() ;
    const std::string getColor() ;
    const std::string getSymbol() ;
    std::string getPath();

    // Functions
    void drawTo(sf::RenderWindow &window);

    bool isMouseOver(sf::RenderWindow &window);
};

#endif //HELLOSFML_CARD_H