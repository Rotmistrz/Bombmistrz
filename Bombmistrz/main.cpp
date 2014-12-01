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
void endFunction();

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
	sf::VideoMode( sf::VideoMode(static_cast<uint>(r.w), static_cast<uint>(r.h), 32)),
	"OpenGL",
	sf::Style::Titlebar | sf::Style::Close, settings);
	
	glewExperimental = GL_TRUE;
	glewInit();
	atexit(endFunction);
		
	auto vec = Map::loadMapFromFile("mapa.txt");
	auto map = std::make_shared<Map>(r.w, r.h, *vec);
	float offset = float(std::min(r.w, r.h) / vec->size());
	Vertex2f v1{ 50, 0 };
	Vertex3f v3{ 1.0f, 0.0f, 0.0 };
	Player p(v1, float(std::min(r.w, r.h) / vec->size()) * 0.8f , v3, r.w, r.h, map.get());
	if (vec == nullptr) {
		MessageBox(0, "Nie mozna wczytac mapy!!!!", 0, 0);
	}
	Vertex2f v11{ 0, r.w };
	Vertex2f v22{ 0, r.h - float(std::min(r.w, r.h) / vec->size()) };
	Vertex3f v33{ 1.0f, 1.0f, 0.0 };
	//Vertex3f v333{ .0f, .0f, .0f };
	Player p2(v22, float(std::min(r.w, r.h) / vec->size()) * 0.8f, v33, r.w, r.h, map.get());
	std::vector<Player> v;
	v.push_back(p);
	v.push_back(p2);
	auto pm = std::make_shared<PlayerManager>(std::move(v)); //= new PlayerManager(std::move(v));
	auto bombs = std::make_shared<BombManager>(
		Vertex2f{ static_cast<float>(r.w) / 2.0f, static_cast<float>(r.h) / 2.0f },
		pm->getPlayer(1)->getSide(),
		Vertex3f{ .0f, 1.0f, 1.0f },
		r.w,
		r.h);
	Game game(pm, map, bombs, r.w, r.h);
	game.genVertexBuffer();
	game.LoadAndcompileShaders();
	game.setLayout();
	game.bindAndUploadTex();
	
	
	bool wasPressedSpace = false;
	bool wasPressedQ = false;
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
			pm->getPlayer(1)->moveLeft(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			pm->getPlayer(1)->moveRight(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			pm->getPlayer(1)->moveUp(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			pm->getPlayer(1)->moveDown(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (wasPressedSpace == false) {
				game.setBomb(pm->getPlayer(1)->getPosition());
				wasPressedSpace = true;
			}
		}
		else {
			if (wasPressedSpace == true) {
				wasPressedSpace = false;
			}
		}
		
		//logika klawiatura - wsad
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			pm->getPlayer(2)->moveUp(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			pm->getPlayer(2)->moveDown(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			pm->getPlayer(2)->moveLeft(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			pm->getPlayer(2)->moveRight(elapsed_time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			if (wasPressedQ == false) {
				game.setBomb(pm->getPlayer(2)->getPosition());
				wasPressedQ = true;
			}
		}
		else {
			if (wasPressedQ == true) {
				wasPressedQ = false;
			}
		}

		//wyczysczenie bufora na kolor czarny
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		bombs->updateTime(elapsed_time);
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

void endFunction() {
	std::cerr << "Raptowne przerwanie programu!";
}