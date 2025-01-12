#pragma once
#include "GameObject.h"
#include "MSound.h"

class Button : public GameObject {

public:
	int id;
	bool clicked = false;
	Vector2f textPos;
	Vector2f sTextPos;
	string text;
	int textSize;
	Vector2f sPos;
	//identidikator koji je kliknut
	Button(int id, Vector2f pos, string textStr, string text, Vector2f textPos, int textSize = 16)
		:GameObject(pos, textStr, GameObject::NONE)
	{
		this->id = id;

		sTextPos = textPos;
		this->textPos = pos + sTextPos;
		this->text = text;
		this->textSize = textSize;
		sPos = Vector2f(pos.x, pos.y);
	}


	void update() {

		Vector2i mousePos = sf::Mouse::getPosition(*Utils::get().window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (getRect().contains(Vector2f(mousePos.x, mousePos.y)) && !clicked) {
				clicked = true;
				MSound::get().playSound("click");
			}
		}
		else {
			clicked = false;
		}

		if (clicked) {
			pos.y = sPos.y + 5;
		}
		else
		{
			pos.y = sPos.y;
		}
		this->textPos = pos + sTextPos;
	}

	void draw() {


		GameObject::draw();
		Utils::get().showText(text, textPos.x, textPos.y, textSize, Color::Black);
	}

};