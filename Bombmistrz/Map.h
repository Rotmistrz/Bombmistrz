#pragma once
#include "Header.h"
#include "Brick.h"
#include <vector>

class Map {
//	void loadBrick(const Brick&);
//	void loadBrick(Brick);
//	void loadBricksFromVector(const std::vector<Brick>&);

	GLuint brickTextID;
	sf::Image imgData;

	std::vector<Brick> vec;
	std::vector<float> corVec;
public:
	Map(const std::vector<Brick>&);
	~Map();

	bool loadImageFromFile(const std::string&);
	void bindAndUpload();

//	Brick* getBrick(uint);

	inline GLuint getSize() {
		return corVec.size();
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

//	bool loadMap(const std::string&);
};

