
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <bits/stdc++.h>

using namespace sf;
using namespace std;
#ifndef HELLOSFML_CARDS_H
#define HELLOSFML_CARDS_H

class Cards{
private:
    int number;
    bool hidden;
    string path ,path_hidden, path_not_hidden;
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
    RectangleShape rec1; // rectangle shape maybe replaced with sprite
    Texture c1;
public:
    // Contructors
    Cards() {
        hidden = 1;
        number = 0;
        path_hidden = "img/hidden_card.jpg";
        path = path_hidden;
        card_clr = black;
        card_symb = clover;
        rec1.setSize(Vector2f (120, 160));
        rec1.setOutlineColor(Color::White);
    }
    Cards(int num, std::string symb) {
        hidden = 1;
        number = num;
        rec1.setSize(Vector2f (120, 160));
        path_hidden = "img/hidden_card.jpg";
        path = path_hidden;
        setSymbolClr(symb);
        path_not_hidden = "img/"+ to_string(number) + symb + ".png"; // will be number not 1
    }
    // Setters
    void setNumber(int num){
        number = num;
    }
    void setHidden(bool h){
        hidden = h;
        if(hidden){
            path = path_hidden;
        }
        else{
            path = path_not_hidden;
        }

    }
    void setSymbolClr(std::string symb){
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
    void setPosition(sf::Vector2f pos){
        rec1.setPosition(pos);
        if (!c1.loadFromFile(path)) {
            cout << "Load failed" << std::endl;
            system("pause");
        }
        rec1.setTexture(&c1);
    }

    // Getters
    const int getNumber() {
        return number;
    }
    const int getHidden() {
        return hidden;
    }
    const std::string getColor() {
        if (card_clr == red)
            return "red";
        else
            return "black";
    }
    const std::string getSymbol() {
        if (card_symb == hearts)
            return "hearts";
        else if (card_symb == clover)
            return "clover";
        else if (card_symb == diamond)
            return "diamond";
        else
            return "spades";
    }
    string getPath(){
        if(hidden){
            path = path_hidden;
        }
        else{
            path = path_not_hidden;
        }
        return path;
    }

    // Functions
    void drawTo(sf::RenderWindow &window){
        window.draw(rec1);
    }

    bool isMouseOver(sf::RenderWindow &window){
        int mouseX = sf::Mouse::getPosition(window).x;
        int mouseY  = sf::Mouse::getPosition(window).y;

        float cardsPosX = rec1.getPosition().x;
        float cardsPosY = rec1.getPosition().y;

        float cardsXPosWidth = rec1.getPosition().x + rec1.getLocalBounds().width;
        float cardsYPosHeight = rec1.getPosition().y + rec1.getLocalBounds().height;
        if(mouseX < cardsXPosWidth && mouseX > cardsPosX && mouseY < cardsYPosHeight && mouseY > cardsPosY ){
            return true;
        }
    }
};


#endif //HELLOSFML_CARDS_H
