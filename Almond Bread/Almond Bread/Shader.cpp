#include "Shader.h"

std::string read_shader_source(std::string _url)
{
	char ch;
	std::string shader;
	std::fstream in(_url, std::fstream::in);
	while (in >> std::noskipws >> ch)
	{
		shader += ch;
	}
	return shader;
}

Shader::Shader(std::string _fragURL, std::string _vertURL)
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const char* f_shaderSource;
	std::string f_string = read_shader_source(_vertURL);
	f_shaderSource = f_string.c_str();

	glShaderSource(vertexShader, 1, &f_shaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	f_string = read_shader_source(_fragURL);
	f_shaderSource = f_string.c_str();

	glShaderSource(fragmentShader, 1, &f_shaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glUseProgram(ID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

VertexBuffer::VertexBuffer(unsigned int _size, float _vertexData[], unsigned int _type)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, _size, _vertexData, _type);
}

VertexArray::VertexArray(unsigned int _size, float _vertexData[], unsigned int _type, VertexBuffer _vbo)
{
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo.ID);
	glBufferData(GL_ARRAY_BUFFER, _size, _vertexData, _type);

}