#include "Header.h"
#include "PlayerManager.h"

float width = 800;
float hight = 600;

int main(int __arg0, char** __arg1) {
	
	//ustawienie kontekstu w specjalnej strukturze
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	//tworzenie okienka
	sf::Window window(
		sf::VideoMode(sf::VideoMode(static_cast<uint>(width), static_cast<uint>(hight), 32)),
		"OpenGL",
		sf::Style::Titlebar | sf::Style::Close, settings);

	glewExperimental = GL_TRUE;
	glewInit();

	Vertex2f v1  { -1.0, 1.0 };
	Vertex2f v2 { 0.0, 0.0 };
	Vertex3f v3{ 1.0f, 0.0f, 0.0 };
	Player p(v1, v2, v3);
	Vertex2f v11{ 0.0, 0.0 };
	Vertex2f v22{ 1.0, -1.0 };
	Vertex3f v33{ 1.0f, 0.0f, 0.0 };
	Player p2(v11, v22, v33);
	std::vector<Player> v;
	v.push_back(p);
	v.push_back(p2);
	PlayerManager pm(&v);
	pm.genVertexBuffer();
	pm.LoadAndcompileShaders();
	pm.setLayout();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else
			if (event.KeyPressed == sf::Keyboard::W) {

			}
			else
			if (event.KeyPressed == sf::Keyboard::S) {

			}
			else
			if (event.KeyPressed == sf::Keyboard::A) {

			}
			else
			if (event.KeyPressed == sf::Keyboard::D) {

			}
		}
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		pm.drawAll();
		window.display();
		
	}
	
	return 0;
}

