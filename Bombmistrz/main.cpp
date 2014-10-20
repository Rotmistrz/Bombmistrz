#include "Header.h"

float width = 800;
float hight = 600;

int main(int __arg0, char** __arg1) {
	//inicjalizacja glewa
	glewInit();
	//ustawienie kontekstu w specjalnej strukturze
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	//tworzenie okienka
	sf::Window window(
		sf::VideoMode(static_cast<uint>(width), static_cast<uint>(hight)),
		"OpenGL",
		sf::Style::Titlebar | sf::Style::Close, settings);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.display();
	}
	
	return 0;
}