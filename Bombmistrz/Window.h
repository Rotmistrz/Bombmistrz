#pragma once
#include "Header.h"

class Window {
	uint depthBits;
	uint stencilBits;
	uint antialiasingLevel;

	sf::ContextSettings settings;
	sf::Window window;
public:

	Window(uint, uint, uint);
	~Window();

	inline void display() {
		window.display();
	}
};

