#pragma once
#include "GameObject.h"
#include "Utils.h"

class Player : public GameObject {
public:

    Player(Vector2f pos)
        : GameObject(pos, "assets/player.png", TYPE::PLAYER) {
        speed = 500.0f; // brzina igraca
    }

    // u svakon frameu se  azrurira stanje igraca
    void update() {
        float deltaTime = Utils::get().deltaTime;

        // kretanje sa A
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            pos.x -= speed * deltaTime;  //smanjuje x kord igraca kako bi ga micalo u livo
            this->flipX = true; // za vizualno okretanje spritea
        }
        // kretanje sa D
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            pos.x += speed * deltaTime; //povecaje kord igraca kako bi isa desno
            this->flipX = false;// vizualno okretanje spritea
        }

        // ogranicavamo prostor za kretanje u okvire ekrana
        if (pos.x < 0) pos.x = 0;
        if (pos.x > Utils::get().window->getSize().x - getRect().width) {
            pos.x = Utils::get().window->getSize().x - getRect().width;
        }
    }
};
