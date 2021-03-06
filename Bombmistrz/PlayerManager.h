#pragma once
#include "Header.h"
#include "Player.h"


class PlayerManager {
	/*GLuint vertexBufferId;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	GLchar* vertSource = nullptr;
	GLchar* fragSource = nullptr;
	uint sizeVS = 0;
	uint sizeFS = 0;

	GLuint posAttrib;
	GLuint colAttrib;

	GLuint _uniform_vec2;*/
	std::vector<Player>* vec;
	std::vector<bool> activePlayers;
	std::vector<float> corVec;
public:
	PlayerManager(std::vector<Player>*);
	PlayerManager(std::vector<Player>&&);
	~PlayerManager();

//	GLchar* loadShader(
//		const std::string&, 
//		uint&);
//	void genVertexBuffer();
//	void setLayout();
//	void LoadAndcompileShaders();
//	inline GLuint getVertexBufferId() {
//		return vertexBufferId;
//	}
	
//	void draw(uint);
//	void drawAll();

	Player* getPlayer(uint);

	inline GLuint getCorSize() {
		return corVec.size();
	}

	inline GLuint getSize() {
		return vec->size();
	}

	inline GLuint GetSizeInBytes() {
		return corVec.size() * sizeof(float);
	}

	inline float* getFirstTabElement() {
		return &corVec[0];
	}

	inline float* getLastTabElement() {
		return &corVec[corVec.size() - 1];
	}

	inline bool isActive(int __i) {
		assert(__i > 0 && __i <= activePlayers.size());
		return activePlayers[__i - 1];
	}

	std::vector<int> isPlayers(int, int);
	void removePlayer(int);
};

