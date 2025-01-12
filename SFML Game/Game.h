#pragma once

#include "GameObject.h"
#include "Button.h"
#include "MSound.h"
#include "Player.h"
#include "EnemyObject.h"
#include "GameOver.h"

class Game : public Screen
{
	vector<EnemyObject*> gameObjects;
	vector<Button*> buttons;

	Player* player;

	int score = 0;
	sf::Clock spawnClock; //sat za kontrolu spawnanja
	float spawnInterval = 1.0f; // Brzina stvaranja enemya

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

public:

	Game() {
		//stvara playera na donji dio ekrana  u centar
		player = new Player(Vector2f(Utils::get().window->getSize().x / 2, Utils::get().window->getSize().y - 150));

		if (!backgroundTexture.loadFromFile("assets/background.png")) {

		}
		backgroundSprite.setTexture(backgroundTexture);

	}

	void update() {

		score += 1;
		player->update();

		spawnEnemy();

		//provjera jeli doslo do interakcije igraca i enemya 
		for (EnemyObject* enemy : gameObjects) {
			if (enemy->isColloide(player)) {
				//ako dode do sudara score se prosljeduje i prebacuje se na quit screen
				Utils::get().saveScore(score);
				Utils::get().currentGame = new GameOver(score);
			}
		}

		// azurira stanje neprijatelja
		for (size_t i = 0; i < gameObjects.size(); ++i) {
			gameObjects[i]->update();

			// brise enemy ako ode sa ekrana
			if (gameObjects[i]->getPos().y > Utils::get().window->getSize().y) {
				delete gameObjects[i];
				gameObjects.erase(gameObjects.begin() + i);
				--i;
			}
		}
	}

	void spawnEnemy() {
		// ogranicenje broja neprijatelja
		if (gameObjects.size() < 10 && spawnClock.getElapsedTime().asSeconds() > spawnInterval) {

			std::string textures[] = {
				"assets/o1.png",
				"assets/o2.png",
				"assets/o3.png"
			};

			// random generira gdje ce se stvorit iduci enemy unutrar ekrana
			float x = static_cast<float>(rand() % Utils::get().window->getSize().x - 50);
			// nasumicno odabere sprite
			std::string texture = textures[rand() % 3];

			// kreira enemya na random generiranoj x lokaciji
			EnemyObject* enemy = new EnemyObject(Vector2f(x, -50), texture);

			// da svi ne padaju iston brzinon
			enemy->setSpeed(200.0f + static_cast<float>(rand() % 100));
			//dodaje enemye u vektor
			gameObjects.push_back(enemy);


			spawnClock.restart();

			spawnInterval -= 0.01f;
			if (spawnInterval <= 0.1) {
				spawnInterval = 0.1f;
			}
		}
	}


	//void onMouseDown(Event e) {
	//}

	//void onKeyDown(Event e) {

	//}

	void draw() {
		//crtanje pozadine
		Utils::get().window->draw(backgroundSprite);

		//crta enemye koji se nalaze u game objects
		for (GameObject* obj : gameObjects) {
			obj->draw();

		}

		player->draw();

		for (Button* button : buttons) {
			button->draw();
		}

		Utils::get().showText("score: " + to_string(score), 10, 10, 20, Color::White);
	}


};