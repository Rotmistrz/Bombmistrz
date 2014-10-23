#pragma once
#include "Header.h"



class PlayerManager {
	GLuint vertexBufferId;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

	GLuint posAttrib;
	GLuint colAttrib;

	std::vector<Player>* vec;
	std::vector<float> corVec;
public:
	PlayerManager(std::vector<Player>*);
	~PlayerManager();

	void genVertexBuffer();
	void setLayout();
	void LoadAndcompileShaders();
	inline GLuint getVertexBufferId() {
		return vertexBufferId;
	}
	
	void draw(uint);
	void drawAll();
};

