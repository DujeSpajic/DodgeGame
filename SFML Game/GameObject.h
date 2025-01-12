#pragma once
#include "Utils.h"

class GameObject {
protected:

	Vector2f pos;
	sf::Sprite sprite;
	Texture texture;
	float speed;
public:
	enum TYPE {
		NONE,
		ENEMY,
		PLAYER
	};
	TYPE type;
	bool destroyFlag = false;
	bool flipX = false;

	GameObject(Vector2f pos, string textureStr, TYPE type) {
		this->pos = pos;
		texture = Texture();
		texture.loadFromFile(textureStr);
		this->sprite.setTexture(texture);
		this->type = type;
	}

	GameObject(Vector2f pos) {
		this->pos = pos;
	}


	//virtual void update() {

	//}

	virtual void draw() {

		if (flipX) {
			sprite.setScale(Vector2f(-1, 1));
			sprite.setPosition(Vector2f(pos.x + getRect().width, pos.y));
		}
		else {
			sprite.setScale(Vector2f(1, 1));
			sprite.setPosition(pos);
		}


		Utils::get().window->draw(sprite);
	}


	virtual FloatRect getRect() {
		return FloatRect(pos.x, pos.y, sprite.getTexture()->getSize().x, sprite.getTexture()->getSize().y);
	}

	bool isColloide(GameObject* other) {

		FloatRect rect = getRect();
		FloatRect otherRect = other->getRect();
		//provjerava jeli doslo do presjeka pravokutnika playera i enemya
		bool r = rect.intersects(otherRect);
		return r;
	}

	virtual void onCollide(GameObject* other) {}


	Vector2f getPos() const {
		return pos;
	}

	void setPos(Vector2f p) {
		pos = p;
	}

	//racuna i vraca sredinu objekta
	Vector2f getCenter() {
		float x = getRect().left + getRect().width / 2;
		float y = getRect().top + getRect().height / 2;
		return Vector2f(x, y);
	}

};