#pragma once
#include "Mathv.h"

class Triangle
{
public:
	float vertices[9];
	Triangle(Vect3 _a = Vect3(0.0f, 0.0f, 0.0f), Vect3 _b = Vect3(0.0f, 0.0f, 0.0f), Vect3 _c = Vect3(0.0f, 0.0f, 0.0f));
	//Triangle(Vect3 _a, Vect3 _b, Vect3 _c);
};

class TriangleBuffer
{
public:
	float* vertices;
	Triangle* triangles;
	unsigned int len = 0;
	TriangleBuffer(Triangle _init = Triangle(Vect3(0.0f,0.0f,0.0f), Vect3(0.0f, 0.0f, 0.0f), Vect3(0.0f, 0.0f, 0.0f)));
	//TriangleBuffer(Triangle _init);
	void AddTriangle(Triangle _t);
	void RemoveTriangle(unsigned int _i);
};