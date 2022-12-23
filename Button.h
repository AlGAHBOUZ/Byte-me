
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <bits/stdc++.h>

using namespace sf;
using namespace std;
#ifndef HELLOSFML_BUTTON_H
#define HELLOSFML_BUTTON_H

class Button{

public:
    Button() {

    }
    Button(std::string t, sf::Vector2f size,  int charSize ,sf::Color bgColor, sf::Color textColor) {
        text.setString(t);
        text.setColor(textColor);
        text.setCharacterSize(charSize);

        button.setSize(size);
        button.setFillColor(bgColor);
    }

    void setFont(sf::Font &font){
        text.setFont(font);
    }
    void setbackColor(sf:: Color color){
        button.setFillColor(color);
    }
    void setTextColor(sf:: Color color){
        text.setColor(color);
    }


    void setPosition(sf::Vector2f pos){
        button.setPosition(pos);
        float xPos = (pos.x + button.getLocalBounds().width/5) - (text.getLocalBounds().width/2);
        float yPos = (pos.y + button.getLocalBounds().height/5) - (text.getLocalBounds().height/2);
        text.setPosition({xPos, yPos});
    }

    void drawTo(sf::RenderWindow &window){
        window.draw(button);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow &window){
        int mouseX = sf::Mouse::getPosition(window).x;
        int mouseY  = sf::Mouse::getPosition(window).y;

        float btnPosX = button.getPosition().x;
        float btnPosY = button.getPosition().y;

        float btnXPosWidth = button.getPosition().x + button.getLocalBounds().width;
        float btnYPosHeight = button.getPosition().y + button.getLocalBounds().height;
        if(mouseX < btnXPosWidth && mouseX > btnPosX && mouseY < btnYPosHeight && mouseY > btnPosY ){
            return true;
        }
    }

private:
    sf::RectangleShape button;
    sf::Text text;
};




#endif //HELLOSFML_BUTTON_H
