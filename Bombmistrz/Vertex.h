#pragma once
#include <initializer_list>

struct Vertex2f {
	float x, y;

	Vertex2f& operator=(float __num) {
		x = y = __num;
		return *this;
	}
};

struct Vertex3f {
	float x;
	float y;
	float z;

	Vertex3f& operator=(float __num) {
		x = y = z = __num;
		return *this;
	}

	/*Vertex3f v;
	Vertex3f w;
	v = w;*/
};

struct Vertex4f {
	float x, y, z, t;
};