#include "Map.h"

void Map::setCorVec() {
	for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
		std::vector<float> _tmp = itr->giveFloatVec();
		for (auto itr2 = _tmp.begin(); itr2 != _tmp.end(); ++itr2) {
			corVec.push_back(*itr2);
		}
	}
}

Map::Map(const std::vector<Brick>& __vec)
: vec(__vec) {
	/*
		konstruktor pobiera wektor obiektow typu Brick.
		Nastepnie konwertuje wszystkie koordynaty i kolory(czyli pola kazdego obiektu)
		do wektora, ktory miesci w sobie ciag wszystkich tych danych.
	*/
	setCorVec();
}

Map::Map(uint __w, uint __h, const std::vector<std::vector<char>>& __vec)
: width(__w), height(__h) {
	float _a = 2.0f / static_cast<float>(__vec.size()); //szerokosc danego kwadratu
	float _x1 = -1.0f; // poczatkowy punkt x1
	float _y1 = 1.0f; //y1
	float _x3 = -1.0f + _a; //_x3 jest przesuniety o dlugosc boku kwadratu
	float _y3 = 1.0f - _a; // tak samo z _y3
	for (auto it1 : __vec) {
		for (auto c : it1) { //char
			if (c == '*') { //dla bloczkow zniszczalnych
				vec.push_back(Brick(_x1, _y1, _x3, _y3));
			}
			else
			if (c == '@') { //dla bloszkow niezniszczalnych
				vec.push_back(Brick(_x1, _y1, _x3, _y3));
			}
			// else c == ' ';
			_x1 += _a; 
			_x3 += _a;
		}
		_x1 = -1.0f;
		_x3 = -1.0f + _a;
		_y1 -= _a;
		_y3 -= _a;
	}

	setCorVec();
}

Map::Map() {
}

Map::~Map() {
}

std::vector<std::vector<char>>* Map::loadMapFromFile(const std::string& __str) {
	std::ifstream _file;
	_file.open(__str);

	if (!_file.is_open()) {
		return nullptr;
	}

	std::vector<std::vector<char>>* _resultVec = new std::vector<std::vector<char>>;

	while (!_file.eof()) {
		std::string _tmp;

		std::getline(_file, _tmp);
		std::vector<char> _tmpVec;

		for (auto c : _tmp) {
			_tmpVec.push_back(c);
		}
		_resultVec->push_back(_tmpVec);
	}

	uint _size = _resultVec->begin()->size();//(*_resultVec)[0].size();
	for (auto v : *_resultVec) {
		if (v.size() != _size) {
			MessageBox(0, "Plik Ÿle przygotowany - nierówne wartoœci kolejnych wierszy.", 0, 0);
			return nullptr;
		}
	}

	return _resultVec;
}
/*
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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
*/