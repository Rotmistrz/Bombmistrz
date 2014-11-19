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

	std::vector<Brick*> vec;
	std::vector<float> corVec;

	uint width, height;
	uint numberOfCols = 0;
	uint numberOfRows = 0;
	float aX = .0f;
	float aY = .0f;

	void setCorVec();
public:
	static std::vector<std::vector<char>>* loadMapFromFile(const std::string&);
	
	Map(const std::vector<Brick*>&);
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

	inline uint getNumberOfCols() {
		return numberOfCols;
	}

	inline uint getNumberOfRows() {
		return numberOfRows;
	}

	inline float get_aX() {
		return aX;
	}

	inline float get_aY() {
		return aY;
	}

	inline uint getPosInCols(float __point) {
		float _edge = -1.0f;
		uint _col = 0;
		while (_edge <= 1.0) {
			if (__point <= _edge + aX)
				return _col;
			_col++;
			_edge += aX;
		}
	}

	inline uint getPosInRows(float __point) {
		float _edge = 1.0f;
		uint _row = 0;
		while (_edge >= -1.0) {
			if (__point >= _edge - aY)
				return _row;
			_row++;
			_edge -= aY;
		}
	}

	inline bool isBrick(uint __col, uint __row) {
		assert(__row * numberOfRows + __col < vec.size());
		if (vec[__row * numberOfRows + __col] != nullptr)
			return true;
		return false;
	}
//	bool loadMap(const std::string&);
};

