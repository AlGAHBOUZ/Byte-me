#ifndef HELLOSFML_CARD_H
#define HELLOSFML_CARD_H

#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <bits/stdc++.h>

#define FIRST_CARD_X_POS 155
#define FIRST_CARD_Y_POS 385
#define DRAW_STACK_X_POS 155
#define DRAW_STACK_Y_POS 165

#define DIST_BETWEEN_VECTORS 165
#define DIST_BETWEEN_CARDS 35

#define CARD_WIDTH 120
#define CARD_HEIGHT 168


class Card{
private:
    int number;
    bool hidden;
    sf::Vector2f last_valid_position;
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
    sf::RectangleShape card_sprite;
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
    void set_last_valid_position(float x, float y);

    // Getters
    const int getNumber() ;
    const int getHidden() ;
    const std::string getColor() ;
    const std::string getSymbol() ;
    std::string getPath();
    const sf::Vector2f getPosition();
    sf::Vector2f get_last_valid_position();

    // Functions
    void drawTo(sf::RenderWindow &window);
    void UpdatePosition(int i, int j);
    sf::FloatRect getGlobalBounds();
    bool isMouseOver(sf::RenderWindow &window);
};

#endif //HELLOSFML_CARD_H