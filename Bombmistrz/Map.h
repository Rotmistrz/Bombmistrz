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

	uint width, height;

	void setCorVec();
public:
	static std::vector<std::vector<char>>* loadMapFromFile(const std::string&);
	
	Map(const std::vector<Brick>&);
	Map(uint, uint, const std::vector<std::vector<char>>&);
	Map();
	~Map();
	
//	bool loadImageFromFile(const std::string&);
//	void bindAndUpload();
//	Brick* getBrick(uint);

	inline GLuint getCorSize() {
		return corVec.size();
	}

	inline GLuint getSize() {
		return vec.size();
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

