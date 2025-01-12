
#pragma once


#include "Screen.h"
#include "Button.h"
#include "Game.h"
#include "MSound.h"


class MainMenu : public Screen
{
	vector<GameObject*> gameObjects;
	vector<Button*> buttons;
	bool showHighScore = false;

	vector<int> scores;
public:
	//main menu konstruktor  sa 3 buttona na ekranu
	MainMenu() {

		buttons.push_back(new Button(0, Vector2f(20, 200), "assets/btn.png", "Play", Vector2f(105, 22), 24));
		buttons.push_back(new Button(1, Vector2f(20, 300), "assets/btn.png", "HighScore", Vector2f(72, 22), 24));
		buttons.push_back(new Button(2, Vector2f(20, 400), "assets/btn.png", "Quit", Vector2f(105, 22), 24));
		//pokrece muziku
		MSound::get().playMusic();
	}

	void update() {
		for (Button* button : buttons) {
			button->update();
			if (!button->clicked) {
				continue;
			}

			switch (button->id)
			{//id 0 pokrece igru
			case 0:
				Utils::get().currentGame = new Game();
				break;
			case 1://id 1 pali high scores
				showHighScore = true;
				scores = Utils::get().readScores();
				sort(scores.begin(), scores.end(), greater<int>());
				break;
			case 2://id 2 gasi igru
				exit(1);
				break;
			}
		}
	}

	//	void onMouseDown(Event e) {}

	//	void onKeyDown(Event e) {}

		//crta sve gumbe
	void draw() {
		for (GameObject* obj : gameObjects) {
			obj->draw();
		}

		if (showHighScore) {
			Utils::get().showText("Top 10 scores!", 400, 200, 24, Color::White);

			int y = 240;

			for (int i = 0; i < 10 && i < scores.size(); i++) {
				Utils::get().showText(to_string(scores[i]), 400, y, 18, Color::White);
				y += 30;
			}


		}



		Utils::get().showText("Dodge game", 200, 50, 50, Color::White);
		for (Button* b : buttons) {
			b->draw();
		}
	}


};

