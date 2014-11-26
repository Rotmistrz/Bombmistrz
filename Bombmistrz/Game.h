#pragma once
#include "Header.h"
#include "PlayerManager.h"
#include "Map.h"
#include "BombManager.h"

class Game {
public:
	GLuint vertexBufferId;
	std::shared_ptr<PlayerManager> playerManager;
	std::unique_ptr<BombManager> bombManager;
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
	GLuint texturesId[2];

	GLuint uniformPlayers;
public:
	Game();
	Game(const std::shared_ptr<PlayerManager>&, const std::shared_ptr<Map>&);
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

