#include "Triangle.h"

Triangle::Triangle(Vect3 _a, Vect3 _b, Vect3 _c)
{
	vertices[0] = _a.x;
	vertices[1] = _a.y;
	vertices[2] = _a.z;
	vertices[3] = _b.x;
	vertices[4] = _b.y;
	vertices[5] = _b.z;
	vertices[6] = _c.x;
	vertices[7] = _c.y;
	vertices[8] = _c.z;
}
TriangleBuffer::TriangleBuffer(Triangle _init)
{
	len = 1;
	triangles = new Triangle[1];
	vertices = new float[9];

	triangles[0] = _init;

	for (unsigned int i = 0; i < 9; i++)
	{
		vertices[i] = _init.vertices[i];
	}
}

void TriangleBuffer::AddTriangle(Triangle _t)
{
	Triangle* t_swap = new Triangle[len];
	for (unsigned int i = 0; i < len; i++)
	{
		t_swap[i] = triangles[i];
	}

	len++;
	triangles = new Triangle[len];
	for (unsigned int i = 0; i < len - 1; i++)
	{
		triangles[i] = t_swap[i];
	}

	triangles[len - 1] = _t;

	vertices = new float[len * 9];
	for (unsigned int i = 0; i < len; i++)
	{
		for (unsigned int j = 0; j < 9; j++)
		{
			vertices[(i * 9) + j] = triangles[i].vertices[j];
		}
	}
}