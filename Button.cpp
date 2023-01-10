
#include "Button.h"
Button::Button(std::string t, sf::Vector2f size,  int charSize ,sf::Color bgColor, sf::Color textColor) {
    text.setString(t);
    text.setColor(textColor);
    text.setCharacterSize(charSize);

    button.setSize(size);
    button.setFillColor(bgColor);
}


void Button::setFont(sf::Font &font){
    text.setFont(font);
}
void Button::setbackColor(sf:: Color color){
    button.setFillColor(color);
}
void Button::setTextColor(sf:: Color color){
    text.setColor(color);
}

void Button::setPosition(sf::Vector2f pos){
    button.setPosition(pos);
    float xPos = (pos.x + button.getLocalBounds().width/5) - (text.getLocalBounds().width/2);
    float yPos = (pos.y + button.getLocalBounds().height/5) - (text.getLocalBounds().height/2);
    text.setPosition({xPos, yPos});
}

void Button::drawTo(sf::RenderWindow &window){
    window.draw(button);
    window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow &window){
    if (button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
        return true;
    }
    else{
        return false;
    }
}