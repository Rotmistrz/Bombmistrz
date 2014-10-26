#pragma once
#include "Header.h"



class PlayerManager {
	GLuint vertexBufferId;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	GLchar* vertSource = nullptr;
	GLchar* fragSource = nullptr;
	uint sizeVS = 0;
	uint sizeFS = 0;

	GLuint posAttrib;
	GLuint colAttrib;

	GLuint _uniform_vec2;
	std::vector<Player>* vec;
	std::vector<float> corVec;
public:
	PlayerManager(std::vector<Player>*);
	~PlayerManager();

	GLchar* loadShader(
		const std::string&, 
		uint&);
	void genVertexBuffer();
	void setLayout();
	void LoadAndcompileShaders();
	inline GLuint getVertexBufferId() {
		return vertexBufferId;
	}
	
	void draw(uint);
	void drawAll();

	Player* getPlayer(uint);
};

