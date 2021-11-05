#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

class Shader
{
public:
	Shader(std::string _fragURL = "", std::string _vertURL = "");
	unsigned int ID;
};

class VertexBuffer
{
public:
	VertexBuffer(unsigned int _size = 0, float _vertexData[] = {}, unsigned int _type = GL_STATIC_DRAW);
	unsigned int ID;
};

class VertexArray
{
public:
	VertexArray(unsigned int _size = 0, float _vertexData[] = {}, unsigned int _type = GL_STATIC_DRAW, VertexBuffer _vbo = VertexBuffer());
	unsigned int ID;
};