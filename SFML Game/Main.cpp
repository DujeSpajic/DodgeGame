#include <SFML/Graphics.hpp>
#include "Utils.h"
#include "MainMenu.h"
int main()
{

    Utils::get().window = new sf::RenderWindow(sf::VideoMode(600, 700), "Dodge game");
    //pali se random number generator,postavlja font, i framerate limit
    Utils::get().init();

    //postavljanje pocetnog prozora na main menu
    Utils::get().currentGame = new MainMenu();


    //game loop
    while (Utils::get().window->isOpen())
    {
        Utils::get().tickClock();
        sf::Event event;
        while (Utils::get().window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                Utils::get().window->close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                Utils::get().currentGame->onMouseDown(event);
            }
            else if (event.type == Event::KeyPressed) {
                Utils::get().currentGame->onKeyDown(event);
            }
        }
        //ciscenje prozora za novi frame
        Utils::get().window->clear({ 23,23,23 });

        Utils::get().currentGame->update();
        Utils::get().currentGame->draw();

        Utils::get().window->display();
    }

    return 0;
}