#pragma once
#include "Header.h"
#include "PlayerManager.h"
#include "Map.h"
#include "BombManager.h"

class Game {
	uint width;
	uint height;

	GLuint vertexBufferId;
	GLuint bombBufferId;
	GLuint vao; //moze bedzie w przyszlosci potrzebne dla roznych layoutow potoku renderowania
	GLuint bombVao;
	std::shared_ptr<PlayerManager> playerManager;
	std::shared_ptr<BombManager> bombManager;
	std::shared_ptr<Map> map;

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	GLchar* vertSource = nullptr;
	GLchar* fragSource = nullptr;
	uint sizeVS = 0;
	uint sizeFS = 0;

	GLuint posAttrib;
	GLuint colAttrib;
	GLuint texAttrib;
	sf::Image imgData;
	// 0 -> map tex, 1 -> players tex, 2 -> bomb tex
	GLuint texturesId[3];

	GLuint uniformPlayers;
	GLuint uniformBomb;

	//odrysowanie bomb
	void drawBombs();

	//odrysowanie wszystkich graczy
	void drawPlayers();

	//odrysowanie mapy
	void drawMap();

	//odrysowanie i-tego gracza
	void draw(uint);
public:
	Game(uint, uint);
	Game(
		const std::shared_ptr<PlayerManager>&, 
		const std::shared_ptr<Map>&, 
		const std::shared_ptr<BombManager>&, 
		uint, 
		uint);
	~Game();

	void genVertexBuffer();
	void setLayout();
	GLchar* loadShader(const std::string&, uint&);
	void LoadAndcompileShaders();
	void drawAll();
	Player* getPlayer(uint);

	void bindAndUploadTex();

	void setBomb(Vertex2f);
};

