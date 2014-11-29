#pragma once
#include "Header.h"
#include "Bomb.h"

typedef unsigned int uint;
class BombManager {

	std::vector<Bomb> bombVec;
	std::vector<float> corVec;

	uint numOfBombs = 40;
public:
	BombManager();
	virtual ~BombManager();

	Bomb* getBomb(uint);

	void setCorVec();

	inline GLuint getCorSize() {
		return corVec.size();
	}

	inline GLuint getSize() {
		return bombVec.size();
	}

	inline GLuint GetSizeInBytes() {
		return corVec.size() * sizeof(decltype(corVec[0]));
	}

	inline float* getFirstTabElement() {
		return &corVec[0];
	}

	inline float* getLastTabElement() {
		return &corVec[corVec.size() - 1];
	}
};

