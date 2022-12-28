//
// Created by Dell on 12/25/2022.
//

#include "Card.h"

// Contructors
Card::Card() {
    hidden = 1;
    number = 0;
    path_hidden = "img/hidden_card.jpg";
    path = path_hidden;
    card_clr = black;
    card_symb = clover;
    if (!card_texture.loadFromFile(getPath())) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
    card_sprite.setTexture(card_texture);
    card_sprite.setTextureRect(sf::IntRect (0,0,120,165));
}
Card::Card(int num, std::string symb) {
    hidden = 1;
    number = num;
    card_sprite.setTextureRect(sf::IntRect (0,0,120,165));
    path_hidden = "img/hidden_card.jpg";
    path = path_hidden;
    setSymbolClr(symb);
    path_not_hidden = "img/"+ std::to_string(number) + symb + ".png"; // will be number not 1
    if (!card_texture.loadFromFile(getPath())) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
    card_sprite.setTexture(card_texture);
    card_sprite.setTextureRect(sf::IntRect (0,0,120,165));
}
// Setters
void Card::setNumber(int num){
    number = num;
}
void Card::setHidden(bool h){
    hidden = h;
    if(hidden){
        path = path_hidden;
    }
    else{
        path = path_not_hidden;
    }

}
void Card::setSymbolClr(std::string symb){
    if (symb == "clover"){
        card_symb = clover;
        card_clr = black;
    }
    else if (symb == "spades"){
        card_symb = spades;
        card_clr = black;
    }
    else if (symb == "diamond"){
        card_symb = diamond;
        card_clr = red;
    }
    else{
        card_symb = hearts;
        card_clr = red;
    }
}
void Card::setPosition(sf::Vector2f pos){
    card_sprite.setPosition(pos);
    if (!card_texture.loadFromFile(path)) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
}

// Getters
const int Card::getNumber() {
    return number;
}
const int Card::getHidden() {
    return hidden;
}
const std::string Card::getColor() {
    if (card_clr == red)
        return "red";
    else
        return "black";
}
const std::string Card::getSymbol() {
    if (card_symb == hearts)
        return "hearts";
    else if (card_symb == clover)
        return "clover";
    else if (card_symb == diamond)
        return "diamond";
    else
        return "spades";
}
std::string Card::getPath(){
    if(hidden){
        path = path_hidden;
    }
    else{
        path = path_not_hidden;
    }
    return path;
}

// Functions
void Card::drawTo(sf::RenderWindow &window){
    window.draw(card_sprite);
}

bool Card::isMouseOver(sf::RenderWindow &window){
    if (card_sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        return true;
    else
        return false;
}

