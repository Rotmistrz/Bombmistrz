#include "BombManager.h"

void BombManager::setCorVec() {
	for (auto itr = bombVec.begin(); itr != bombVec.end(); ++itr) {
		auto wsk = *itr; //iterator to wskaznik na wskaznik na jedna cegielke, wiec dla ulatwienia
		//tworzes zwykly wskaznik juz na sama cegielke.
		auto _tmp = wsk.giveFloatVec();
		for (auto itr2 = _tmp.begin(); itr2 != _tmp.end(); ++itr2) {
			corVec.push_back(*itr2);
		}
	}
}

BombManager::BombManager(
	Vertex2f __point, 
	float __side, 
	Vertex3f __color, 
	uint __w, 
	uint __h) {

	for (uint i = 0; i < numOfBombs; i++) {
		bombVec.push_back(Bomb(__point, __side, __color, __w, __h));
	}

	setCorVec();
}

BombManager::~BombManager() {
}

Bomb* BombManager::getBomb(uint __i) {
	uint i = 0; 
	for (auto& b : bombVec) {
		if (i == __i)
			return &b;
		++i;
	}

	return nullptr;
}

void BombManager::setBomb(Vertex2f __pos) {
	for (auto& b : bombVec) {
		if (!b.isActive()) {
			b.set(__pos.x, __pos.y);
			b.setActive();
			return;
		}
	}
}