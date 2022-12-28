#ifndef HELLOSFML_BUTTON_H
#define HELLOSFML_BUTTON_H

#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <bits/stdc++.h>

class Button{

public:

    Button(std::string t, sf::Vector2f size,  int charSize ,sf::Color bgColor, sf::Color textColor);

    void setFont(sf::Font &font);

    void setbackColor(sf:: Color color);

    void setTextColor(sf:: Color color);


    void setPosition(sf::Vector2f pos);

    void drawTo(sf::RenderWindow &window);

    bool isMouseOver(sf::RenderWindow &window);

private:
    sf::RectangleShape button;
    sf::Text text;
};




#endif //HELLOSFML_BUTTON_H
