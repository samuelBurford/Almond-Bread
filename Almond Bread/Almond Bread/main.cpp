#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

#include "Context.h"
#include "Shader.h"
#include "Triangle.h"

int m1_press = 0;
int m2_press = 0;
int kp8_press = 0;
int kp2_press = 0;
int shift_press = 0;
int ctrl_press = 0;

double m_xdelta = 0;
double m_ydelta = 0;
double m_xpos, m_ypos;

double mx0;
double my0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void)
{
	Triangle t1 = Triangle(Vect3(1.0f,1.0f,0.0f), Vect3(1.0f, -1.0f, 0.0f), Vect3(-1.0f, -1.0f, 0.0f));
	TriangleBuffer tB = TriangleBuffer(t1);
	Triangle t2 = Triangle(Vect3(1.0f, 1.0f, 0.0f), Vect3(-1.0f, 1.0f, 0.0f), Vect3(-1.0f, -1.0f, 0.0f));
	tB.AddTriangle(t2);

	GLFWwindow* window;
	Context context(300, 300, "window", 4, 6, GLFW_OPENGL_CORE_PROFILE, window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Called each time window is resized //
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);

	VertexBuffer VBO = VertexBuffer(sizeof(tB.vertices) * tB.len * 9, tB.vertices, GL_STATIC_DRAW);
	Shader shaderProgram = Shader("fragmentShaderSource.glsl", "vertexShaderSource.glsl");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	VertexArray VAO = VertexArray(sizeof(tB.vertices) * tB.len * 9, tB.vertices, GL_STATIC_DRAW, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);




	GLuint FB = 0;
	glGenFramebuffers(1, &FB);
	glBindFramebuffer(GL_FRAMEBUFFER, FB);

	// The texture we're going to render to
	GLuint RT;
	glGenTextures(1, &RT);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, RT);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, RT, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "FRAMEBUFFER:FUCKED" << std::endl;

	Shader FBshaderProgram = Shader("frameBufferFrag.glsl", "vertexShaderSource.glsl");
	GLuint quad_programID = FBshaderProgram.ID;
	GLuint texID = glGetUniformLocation(quad_programID, "renderedTexture");
	GLuint timeID = glGetUniformLocation(quad_programID, "time");



	int u_resolution = glGetUniformLocation(shaderProgram.ID, "u_resolution");
	int u_time = glGetUniformLocation(shaderProgram.ID, "u_time");
	int u_mousePos = glGetUniformLocation(shaderProgram.ID, "u_mousePos");
	int u_zoom = glGetUniformLocation(shaderProgram.ID, "u_zoom");
	int u_maxIter = glGetUniformLocation(shaderProgram.ID, "u_maxIter");
	int u_pass = glGetUniformLocation(shaderProgram.ID, "u_pass");


	int w_height, w_width;
	float time;

	float offsetx = 0.0, offsety = 0.0;

	float zoom = 1.0f;
	int max_iter = 1;
	int pass = 0;

	float offset0x = 0.0f, offset0y = 0.0f, zoom0 = 1.0f;
	int max_iter0 = 1;

	bool swapPass = true;

	

	while (!glfwWindowShouldClose(window)) // glfwWindowShouldClose simply returns a close flag. (top right close button, usually) //
	{

		glBindFramebuffer(GL_FRAMEBUFFER, FB);
		glUseProgram(shaderProgram.ID);

		glfwGetWindowSize(window, &w_width, &w_height);
		time = glfwGetTime();

		glUniform2i(u_resolution, w_width, w_height);
		glUniform1f(u_time, time);

		glfwGetCursorPos(window, &m_xpos, &m_ypos);

		m_xdelta = mx0 - m_xpos;
		m_ydelta = my0 - m_ypos;

		mx0 = m_xpos;
		my0 = m_ypos;

		if (m1_press)
		{
			offsetx = offsetx + ( m_xdelta  * zoom );
			offsety = offsety + ( m_ydelta  * zoom );
			glUniform2f(u_mousePos, offsetx, offsety);
		}

		if (m2_press && ctrl_press)
		{
			zoom = zoom + zoom / 10;
			glUniform1f(u_zoom, zoom);
		}
		else if (m2_press)
		{
			zoom = zoom - zoom / 10;
			glUniform1f(u_zoom, zoom);
		}


		if (kp8_press)
		{
			max_iter = max_iter + 1;
			glUniform1i(u_maxIter, max_iter);
		}

		if (kp2_press)
		{
			max_iter = max_iter - 1;
			if (max_iter == 0)
			{
				max_iter = 1;
			}
			glUniform1i(u_maxIter, max_iter);
		}

		if (offset0x != offsetx || offset0y != offsety || zoom0 != zoom || max_iter0 != max_iter)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glBindVertexArray(VAO.ID);
			//glUseProgram(FBshaderProgram.ID);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glfwSwapBuffers(window);

			swapPass = true;
		}
		else
		{

		}

		offset0x = offsetx;
		offset0y = offsety;
		zoom0 = zoom;
		max_iter0 = max_iter;
		
		glfwPollEvents(); // Processes the queue of events //
	}

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height); // Resizes viewport in relation to the new window width and height //
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
	{
		m1_press = 1;
	}
	else
	{
		m1_press = 0;
	}

	if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS)
	{
		m2_press = 1;
	}
	else
	{
		m2_press = 0;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (mods == 0)
	{
		ctrl_press = 0;
		shift_press = 0;
	}
	else if (mods == 1)
	{
		shift_press = 1;
	}
	else if (mods == 2)
	{
		ctrl_press = 1;
	}

	if (key == GLFW_KEY_KP_8 && action == GLFW_PRESS)
	{
		kp8_press = 1;
	}
	else if (key == GLFW_KEY_KP_8 && action == GLFW_RELEASE)
	{
		kp8_press = 0;
	}
	if (key == GLFW_KEY_KP_2 && action == GLFW_PRESS)
	{
		kp2_press = 1;
	}
	else if (key == GLFW_KEY_KP_2 && action == GLFW_RELEASE)
	{
		kp2_press = 0;
	}
}