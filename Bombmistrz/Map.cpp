#include "Map.h"

void Map::setCorVec() {
	for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
		auto wsk = *itr; //iterator to wskaznik na wskaznik na jedna cegielke, wiec dla ulatwienia
		//tworzes zwykly wskaznik juz na sama cegielke.
		if (wsk != nullptr) {
			auto _tmp = wsk->giveFloatVec();
			for (auto itr2 = _tmp.begin(); itr2 != _tmp.end(); ++itr2) {
				corVec.push_back(*itr2);
			}
		}
		else {
			auto _tmp = Square::giveEmptyFloatVec();
			for (auto itr2 = _tmp.begin(); itr2 != _tmp.end(); ++itr2) {
				corVec.push_back(*itr2);
			}
		}
	}
}

// do modernizacji!!! Trzeba ustawic pola klasy w tym konstruktorze!!!
Map::Map(const std::vector<std::shared_ptr<Brick>>& __vec)
: vec(__vec) {
	assert(0);
	
	/*
		konstruktor pobiera wektor obiektow typu Brick.
		Nastepnie konwertuje wszystkie koordynaty i kolory(czyli pola kazdego obiektu)
		do wektora, ktory miesci w sobie ciag wszystkich tych danych.
	*/
	setCorVec();
}

Map::Map(uint __w, uint __h, const vec2dChar& __vec)
: width(__w), height(__h) {

	float _a_cols = .0f;
	float _a_rows = .0f;
	if (width < height) {
		_a_cols = static_cast<float>(width) / __vec.size();
		_a_rows = _a_cols;
		_a_rows /= static_cast<float>(height);
		_a_cols /= static_cast<float>(width);
		_a_cols *= 2.0f;
		_a_rows *= 2.0f;
	}
	else {
		_a_rows = static_cast<float>(height) / __vec.size();
		_a_cols = _a_rows;
		_a_cols /= static_cast<float>(width);
		_a_rows /= static_cast<float>(height);
		_a_rows *= 2.0f;
		_a_cols *= 2.0f;
	}
	//liczba kolumn i wierszy + dlugosc boku cegielek
	numberOfCols = __vec[0].size();
	numberElementsInRow = __vec[0].size();
	aX = _a_cols;
	aY = _a_rows;

	float _x1 = -1.0f; // poczatkowy punkt x1
	float _y1 = 1.0f; //y1
	float _x3 = -1.0f + _a_cols; //_x3 jest przesuniety o dlugosc boku kwadratu
	float _y3 = 1.0f - _a_rows; // tak samo z _y3
	for (auto it1 : __vec) {
		for (auto c : it1) { //char
			if (c == '*') { //dla bloczkow zniszczalnych
				vec.push_back(std::make_shared<Brick>(Brick(_x1, _y1, _x3, _y3)));
			}
			else
			if (c == '@') { //dla bloszkow niezniszczalnych
				vec.push_back(std::make_shared<Brick>(Brick(_x1, _y1, _x3, _y3)));
			}
			else //jezeli jest wolne miejsce to wloz nullptr
				vec.push_back(nullptr);
			
			_x1 += _a_cols; 
			_x3 += _a_cols;
		}
		_x1 = -1.0f;
		_x3 = -1.0f + _a_cols;
		_y1 -= _a_rows;
		_y3 -= _a_rows;
	}

	setCorVec();
}

Map::Map() {
}

Map::~Map() {
}

ptrVec2dChar Map::loadMapFromFile(const std::string& __str) {
	std::ifstream _file;
	_file.open(__str);

	if (!_file.is_open()) {
		return nullptr;
	}

	auto _resultVec = std::shared_ptr<vec2dChar>(new vec2dChar);

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

void Map::removeElement(uint __row, uint __col) {
	int _index = numberElementsInRow * __row + __col;
	if (_index >= vec.size())
		return;

	vec[numberElementsInRow * __row + __col].reset();
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