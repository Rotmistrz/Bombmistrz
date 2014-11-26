#pragma once
#include "Header.h"
#include "Bomb.h"

class BombManager {

	std::vector<Bomb> bombVec;
	std::vector<float> corVec;
public:
	BombManager();
	virtual ~BombManager();

	Bomb* getBomb(uint);

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

