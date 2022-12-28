#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(1280,960),"Klondike",Style::Titlebar | Style::Close);
    Texture BG;
    if (!BG.loadFromFile("IMG/pal.png")) {
        cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }

    Sprite s(BG);
    s.setTextureRect(IntRect (0,0,1280,960));
    s.setColor(Color(255,255,255,64));

    // Scale BG To Fill
    Vector2u TextureSize = BG.getSize();
    Vector2u WindowSize = window.getSize();
    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;
    s.scale(ScaleX,ScaleY);


    RectangleShape rec1;
    Rect<float> sizeOfRec1 = rec1.getGlobalBounds();
    rec1.setOrigin( Vector2f(sizeOfRec1.width/2, sizeOfRec1.height/2) );
    Vector2f currPosition(1060,85);
    rec1.setPosition(currPosition);
    rec1.setSize(Vector2f (120, 160));

    Texture c1;
    if (!c1.loadFromFile("IMG/Cards/2_of_spades.png")) {
        cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }
    rec1.setTexture(&c1);

    RectangleShape rec2;
    Rect<float> sizeOfRec2 = rec2.getGlobalBounds();
    rec2.setOrigin( Vector2f(sizeOfRec2.width/2, sizeOfRec2.height/2) );
    Vector2f currPosition2(1060,85+35);
    rec2.setPosition(currPosition2);
    rec2.setSize(Vector2f (120, 160));

    Texture c2;
    if (!c2.loadFromFile("IMG/Cards/3_of_spades.png")) {
        cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }
    rec2.setTexture(&c2);



    Event event;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            switch(event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseButtonPressed:
                    if(Mouse::Button::Left == event.mouseButton.button && rec1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                        rec1.setPosition(rec1.getPosition().x-158,85);
                    }
                    break;
            }


            window.clear();
            window.draw(s);
            window.draw(rec1);
            window.draw(rec2);
            window.display();
        }
    }
}
