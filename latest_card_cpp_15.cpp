#include "Card.h"
#define FIRST_CARD_X_POS 155
#define FIRST_CARD_Y_POS 385
#define DIST_BETWEEN_VECTORS 165
#define DIST_BETWEEN_CARDSS 35
#define CARD_WIDTH 120
#define CARD_HEIGHT 168



// Contructors
Card::Card() {
    hidden = 1;
    number = 0;
    path_hidden = "img/pal-back.png";
    path = path_hidden;
    card_clr = black;
    card_symb = clover;
    currPosition = card_sprite.getPosition();
    if (!card_texture.loadFromFile(getPath())) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
    card_sprite.setTexture(&card_texture);
    card_sprite.setSize(sf::Vector2f(CARD_WIDTH,CARD_HEIGHT));
    sf::Rect<float> VarName = card_sprite.getGlobalBounds();
    card_sprite.setOrigin( sf::Vector2f(VarName.width/2, VarName.height/2) );
}
Card::Card(int num, std::string symb) {
    hidden = 1;
    number = num;
    card_sprite.setTextureRect(sf::IntRect (0,0,CARD_WIDTH,CARD_HEIGHT));
    path_hidden = "img/pal-back.png";
    path = path_hidden;
    currPosition = card_sprite.getPosition();
    setSymbolClr(symb);
    path_not_hidden = "img/"+ std::to_string(number) + symb + ".png"; // will be number not 1
    if (!card_texture.loadFromFile(getPath())) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
    card_sprite.setTexture(&card_texture);
    card_sprite.setSize(sf::Vector2f(CARD_WIDTH,CARD_HEIGHT));
    sf::Rect<float> VarName = card_sprite.getGlobalBounds();
    card_sprite.setOrigin( sf::Vector2f(VarName.width/2, VarName.height/2) );
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
        if (!card_texture.loadFromFile(getPath())) {
            std::cout << "Load failed" << std::endl;
            system("pause");
        }
        card_sprite.setTexture(&card_texture);
        card_sprite.setSize(sf::Vector2f(CARD_WIDTH,CARD_HEIGHT));
        sf::Rect<float> VarName = card_sprite.getGlobalBounds();
        card_sprite.setOrigin( sf::Vector2f(VarName.width/2, VarName.height/2) );
//        sf::Vector2u TextureSize = card_texture.getSize();
//        sf::Vector2u WindowSize = sf::Vector2u(1280,960);
//        float ScaleX = (float) WindowSize.x / TextureSize.x;
//        float ScaleY = (float) WindowSize.y / TextureSize.y;
        card_sprite.setScale({1.0f,1.0f});
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

void Card::setCurr(){
    currPosition = getPosition();
}

// Getters

sf::Vector2f Card::getCurr(){
    return currPosition;
}

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

const sf::Vector2f Card::getPosition(){
    return card_sprite.getPosition();
}

// Functions
void Card::drawTo(sf::RenderWindow &window){
    window.draw(card_sprite);
}

void Card::UpdatePosition(int i, int j) {
    float new_pos_x = FIRST_CARD_X_POS + i * DIST_BETWEEN_VECTORS;
    float new_pos_y = FIRST_CARD_Y_POS + j * DIST_BETWEEN_CARDSS;
    setPosition({new_pos_x,new_pos_y});
}

sf::FloatRect Card::getGlobalBounds(){
    return card_sprite.getGlobalBounds();
}

bool Card::isMouseOver(sf::RenderWindow &window){
    if (card_sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        return true;
    else
        return false;
}
