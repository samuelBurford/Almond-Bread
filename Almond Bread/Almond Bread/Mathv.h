#pragma once

struct Vect2_I {
	int x;
	int y;
};
struct Vect2 {
	float x;
	float y;
};
struct Vect3_I {
	int x;
	int y;
	int z;
};
struct Vect3 {
	float x;
	float y;
	float z;
	Vect3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : x(_x), y(_y), z(_z) {}
	//Vect3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};