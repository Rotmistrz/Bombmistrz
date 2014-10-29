#pragma once
#include "Header.h"
#include "Brick.h"

class Map {
	void loadBrick(const Brick&);
	void loadBrick(Brick);
	void loadBricksFromVector(const std::vector<Brick>&);
public:
	Map();
	~Map();

	bool loadMap(const std::string&);

};

