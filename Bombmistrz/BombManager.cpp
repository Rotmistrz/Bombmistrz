#include "BombManager.h"

BombManager::BombManager() {
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