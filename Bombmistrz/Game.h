#pragma once
#include "Header.h"
#include "PlayerManager.h"
#include "Map.h"

class Game {
public:
	GLuint vertexBufferId;
	PlayerManager* playerManager;
	Map* map;

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
	GLuint texturesId[2];

	GLuint uniformPlayers;
public:
	Game();
	Game(PlayerManager*, Map*);
	~Game();

	void genVertexBuffer();
	void setLayout();
	GLchar* loadShader(const std::string&, uint&);
	void LoadAndcompileShaders();
	void draw(uint);
	void drawAll();
	Player* getPlayer(uint);

	void bindAndUploadTex();
};

