#pragma once
#include <SFML/Audio.hpp>
#include <map>


using namespace sf;
using namespace std;



class MSound {

	map<string, SoundBuffer* > sounds;
	sf::Music music;
	sf::Sound sound;

public:



	MSound() {

		music.openFromFile("assets/music.wav");

		sf::SoundBuffer* clickBuffer = new SoundBuffer();
		clickBuffer->loadFromFile("assets/clickBtn.wav");



		sounds.insert(pair<string, SoundBuffer*>("click", clickBuffer));
	}

	~MSound() {
		for (auto& pair : sounds) {
			delete pair.second;
		}
		sounds.clear();
	}

	void playMusic() {
		music.stop();
		music.play();
		music.setLoop(true);
	}

	void playSound(string key) {
		sound.setBuffer(*sounds[key]);
		sound.play();
	}

	static MSound& get() {
		static MSound INSTANCE;
		return INSTANCE;
	}

};