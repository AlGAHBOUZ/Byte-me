#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;
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


int main()
{
    RenderWindow window;
    window.create(VideoMode(1280,800),"Klondike",Style::Default);

    Texture BG;
    if (!BG.loadFromFile("img/pal.jpg")) {
        cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }
    Sprite s(BG);
    s.setTextureRect(IntRect (0,0,1280,800));
    s.setColor(Color(255,255,255,64));
    RectangleShape rec1;
    rec1.setPosition(1060,85);
    rec1.setSize(Vector2f (120, 160));
    rec1.setOutlineColor(Color::White);

    Texture c1;
    if (!c1.loadFromFile("img/d.png")) {
        cout << "Load failed" << std::endl;
        system("pause");
        return -1;
    }
    rec1.setTexture(&c1);
/*
    sf::Texture texture;
    sf::Sprite playerImage;
    if (!texture.loadFromFile("img/d.png"))
    {
        return -1;
    }
    playerImage.setTexture(texture);
    playerImage.setScale(sf::Vector2f(0.5f, 0.5f));
    */
    sf::Font font;
    if (!font.loadFromFile("img/arial.ttf"))
    {
        return -1;
    }
    Button btn1("Start the Game!", {420, 100}, 42, sf::Color::Blue, sf::Color::Black);
    float z = window.getSize().y/2;
    float ab = window.getSize().x/3;
    btn1.setPosition({ab , z});
    btn1.setFont(font);
    sf::Text text;

// select the font
    text.setFont(font); // font is a sf::Font

// set the string to display
    text.setString("Press Enter to start ;) ");

// set the character size
    text.setCharacterSize(42); // in pixels, not points!

// set the color
    text.setFillColor(sf::Color::White);

// set the text style
    text.setStyle(sf::Text::Bold);

    text.setPosition(220.f , window.getSize().y/2);

    bool f = window.isOpen();
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();


                case sf::Event::MouseMoved:
                    if(btn1.isMouseOver(window)){
                        btn1.setbackColor(sf::Color::White);
                    }
                    else{
                        btn1.setbackColor(sf::Color::Green);
                    }
                    break;
                case sf::Event::MouseButtonPressed:{
                    if(btn1.isMouseOver(window)){
                        window.clear();
                        window.draw(s);
                        window.draw(rec1);
                        window.display();
                        f = 0;
                    }
                }

            }


        }
// here lies the enter button
       /* if(f){
            window.clear();
            window.draw(text);
            window.display();
        }

*/

       if(f){
           window.clear();
           window.draw(s);
           btn1.drawTo(window);
           window.display();
       }
       /*
        if(event.type == sf::Event::KeyReleased){
            if(event.key.code == sf::Keyboard::Enter){
                window.clear();
                window.draw(playerImage);
                window.display();
                f = 0;

            }

        }
*/
    }
}
