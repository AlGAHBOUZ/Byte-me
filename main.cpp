#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;

int main()
{
    RenderWindow window;
    window.create(VideoMode(1280,800),"Klondike",Style::Default);
    Texture BG;
    if (!BG.loadFromFile("IMG/pal.png")) {
        cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }
//    Vector2u TextureSize = BG.getSize();
//    Vector2u WindowSize = window.getSize();
//    float ScaleX = (float) WindowSize.x / TextureSize.x;
//    float ScaleY = (float) WindowSize.y / TextureSize.y;
    Sprite s(BG);
//    s.setScale(ScaleX, ScaleY);
    s.setTextureRect(IntRect (0,0,1280,800));
    s.setColor(Color(255,255,255,64));
    RectangleShape rec1;
    rec1.setPosition(1060,85);
    rec1.setSize(Vector2f (120, 160));
    rec1.setOutlineColor(Color::White);

    Texture c1;
    if (!c1.loadFromFile("IMG/Ace.png")) {
        cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }
    rec1.setTexture(&c1);

    Event event;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
            window.clear();
            window.draw(s);
            window.draw(rec1);
            window.display();
        }
    }
}