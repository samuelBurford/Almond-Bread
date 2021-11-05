#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

class Context
{
public:
	Context(unsigned int _height, unsigned int _width, const char* _title, unsigned int _context_version_major, unsigned int _context_version_minor, unsigned int _opengl_profile, GLFWwindow*& _window);
};