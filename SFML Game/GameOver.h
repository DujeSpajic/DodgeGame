#pragma once
#include "Game.h"

class Game;


class GameOver : public Screen
{
	vector<Button*> buttons;
	int score;
public:
	//sprema rezultat koji je bia prikazan na ekranu  
	GameOver(int score) {
		this->score = score;
		//dodaje quit gumb na ekran
		buttons.push_back(new Button(1, Vector2f(200, 300), "assets/btn.png", "Quit", Vector2f(105, 22), 24));
	}

	void update() {
		for (Button* button : buttons) {
			button->update();
			if (!button->clicked) {
				continue;
			}

			switch (button->id)
			{
				//kas se klikne gumb (quit) ugasi se
			case 1:
				exit(1);
				break;
			}
		}
	}

	//void onMouseDown(Event e) {}
	//void onKeyDown(Event e) {}

	//prikazuje game over i rezulat na ekranu
	void draw() {
		Utils::get().showText("Game Over!", 200, 300, 42, Color::Red);
		Utils::get().showText("Score:  " + to_string(score), 200, 400, 42, Color::White);
		for (Button* b : buttons) {
			b->draw();
		}
	}




};

