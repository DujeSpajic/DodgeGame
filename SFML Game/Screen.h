#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Screen {

public:

	virtual void update() {}
	virtual void draw() {}
	virtual void onMouseDown(Event e) {}
	virtual void onKeyDown(Event e) {}

};