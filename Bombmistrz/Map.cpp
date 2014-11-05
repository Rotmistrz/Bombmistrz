#include "Map.h"

Map::Map(const std::vector<Brick>& __vec)
: vec(__vec) {

	for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
		std::vector<float> _tmp = itr->giveFloatVec();
		for (auto itr2 = _tmp.begin(); itr2 != _tmp.end(); ++itr2) {
			corVec.push_back(*itr2);
		}
	}
}

Map::~Map() {
}

bool Map::loadImageFromFile(const std::string& __file_name) {
	bool _result = imgData.loadFromFile(__file_name);

	if (!_result)
		MessageBox(0, "Nie mozna wczytac tekstury do klasy Map!", 0, 0);

	return true;
}

void Map::bindAndUpload() {
	glGenTextures(1, &brickTextID);
	glBindTexture(GL_TEXTURE_2D, brickTextID);

	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_RGBA, 
		imgData.getSize().y, 
		imgData.getSize().x, 
		0, 
		GL_RGBA, 
		GL_UNSIGNED_BYTE, 
		imgData.getPixelsPtr());
}
