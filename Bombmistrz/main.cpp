#include "Header.h"
#include "PlayerManager.h"
#include "Game.h"
#include <string>
#include <sstream>

const float width = 600;
const float hight = 600;

struct Resolution {
	uint w, h;
};

Resolution loadResFromFile(const std::string&);

int main(int __arg0, char* __arg1[]) {
	//ustawienie kontekstu w specjalnej strukturze
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	//tworzenie okienka
	Resolution r;
	try {
		 r = loadResFromFile("rozdzielczosc.txt");
	}
	catch (std::string) {
		MessageBox(0, "chuja nawet nie umiesz podac w pliku txt dwoch intow debilu!", 0, 0);
		return -1;
	}

	sf::Window window(
	sf::VideoMode(sf::VideoMode(static_cast<uint>(r.w), static_cast<uint>(r.h), 32)),
	"OpenGL",
	sf::Style::Titlebar | sf::Style::Close, settings);
	
	glewExperimental = GL_TRUE;
	glewInit();
	
	
	auto vec = Map::loadMapFromFile("mapa.txt");
	float offset = float(std::min(r.w, r.h) / vec->size());
	Vertex2f v1{ 0, 0 };
	Vertex2f v2{ -0.9, 0.9 };
	Vertex3f v3{ 1.0f, 0.0f, 0.0 };
	Player p(v1, float(std::min(r.w, r.h) / vec->size()), v3, r.w, r.h);
	if (vec == nullptr) {
		MessageBox(0, "Nie mozna wczytac mapy!!!!", 0, 0);
	}
	Vertex2f v11{ 0, r.w };
	Vertex2f v22{ 0, r.h - float(std::min(r.w, r.h) / vec->size()) };
	Vertex3f v33{ 1.0f, 1.0f, 0.0 };
	//Vertex3f v333{ .0f, .0f, .0f };
	Player p2(v22, float(std::min(r.w, r.h) / vec->size()), v33, r.w, r.h);
	std::vector<Player> v;
	v.push_back(p);
	v.push_back(p2);
	PlayerManager pm(std::move(v));
	Vertex3f v333{ 1.0f, 1.0f, 1.0f };
	Brick b(v1, v2, v333);
	Brick b2(v11, v22, v333);
	std::vector<Brick> vb;


//	vb.push_back(b);
//	vb.push_back(b2);
	Map map(r.w, r.h, *vec);

	Game game(&pm, &map);
	game.genVertexBuffer();
	game.LoadAndcompileShaders();
	game.setLayout();
	game.bindAndUploadTex();
	

	sf::Clock clock;
	while (window.isOpen()) {
		float elapsed_time = static_cast<float>(clock.getElapsedTime().asSeconds());
		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		//logika klawiatura - strzalki
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			pm.getPlayer(1)->moveLeft(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			pm.getPlayer(1)->moveRight(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			pm.getPlayer(1)->moveUp(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			pm.getPlayer(1)->moveDown(elapsed_time);
		}
		
		//logika klawiatura - wsad
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			pm.getPlayer(2)->moveUp(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			pm.getPlayer(2)->moveDown(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			pm.getPlayer(2)->moveLeft(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			pm.getPlayer(2)->moveRight(elapsed_time);
		}

		//wyczysczenie bufora na kolor czarny
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//renderowanie pierwszego gracza
	//	game.draw(1);
		//renderowanie drugiego gracza
	//	game.draw(2);
		game.drawAll();
		//zamiana buforow -> pokazanie obrazu w okienku
		window.display();
		
	}
	
	return 0;
}

Resolution loadResFromFile(const std::string& __str) {
	std::ifstream _file;
	_file.open(__str);

	if (!_file.is_open())
		throw std::string("blad!");

	std::string _temp("");
	std::getline(_file, _temp);

	std::string _n1;
	std::string _n2;

	bool first = true;
	for (char c : _temp) {
		if (c == ' ') {
			first = false;
			continue;
		}
		if (first)
			_n1 += c;
		else
			_n2 += c;
	}

	uint _n1_i, _n2_i;
	std::istringstream iss(_n1);
	iss >> _n1_i;
	std::istringstream iss_2(_n2);
	iss_2 >> _n2_i;

	Resolution r;
	r.w = _n1_i;
	r.h = _n2_i;
	return r;
}