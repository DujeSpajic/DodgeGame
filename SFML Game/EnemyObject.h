#pragma once
#include "GameObject.h"
#include <vector>
#include <cstdlib>
#include <ctime>

class EnemyObject : public GameObject {
public:

    EnemyObject(Vector2f pos, string texture)
        : GameObject(pos, texture, TYPE::ENEMY) {
        speed = 200.0f; //brzina padanja
    }

    // azuriranje padanja
    void update() {
        float deltaTime = Utils::get().deltaTime;

        //padanje enemya put dole
        pos.y += speed * deltaTime;

        //kad ode off scvreen oznaci ga za brisanje
        if (pos.y > Utils::get().window->getSize().y) {
            destroyFlag = true;
        }
    }
    //omogucava drukcije brzine/izmjene
    void setSpeed(float speed) {
        this->speed = speed;
    }
};
