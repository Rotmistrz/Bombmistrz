#pragma once
#include "Header.h"
#include "Bomb.h"

typedef unsigned int uint;
class BombManager {

	//std::vector przechowywujacy n bomb
	std::vector<Bomb> bombVec;
	//std::vector przechowywujacy informacje o bombach jak polozenie, color, tex gotowa do transferu na gpu
	std::vector<float> corVec;

	//maksymaln ilosc bomb jaka moze przechowywac manager
	uint numOfBombs = 40;
public:
	BombManager(Vertex2f, float, Vertex3f, uint, uint);
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

	void updateTime(float __dt) {
		for (auto& b : bombVec) {
			if (b.isActive())
				b.updateTime(__dt);
		}
	}

	void setBomb(Vertex2f);
};

