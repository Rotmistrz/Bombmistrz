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
		sf::VideoMode(static_cast<uint>(width), static_cast<uint>(hight)),
		"OpenGL",
		sf::Style::Titlebar | sf::Style::Close, settings);

	glewExperimental = GL_TRUE;
	glewInit();

	Vertex2f v1  { -0.5, 0.5 };
	Vertex2f v2 { 0.5, -0.5 };
	Vertex3f v3 { 1.0, .5, 0.5 };
	Player p(v1, v2, v3, 1);
	std::vector<Player> v;
	v.push_back(p);
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
		}
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		pm.draw();
		window.display();
		
	}
	
	return 0;
}