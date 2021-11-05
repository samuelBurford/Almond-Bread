#include "Context.h"

Context::Context(unsigned int _height, unsigned int _width, const char* _title, unsigned int _context_version_major, unsigned int _context_version_minor, unsigned int _opengl_profile, GLFWwindow*& _window)
{
	glfwInit();   // Init GLFW libraries, if we don't do this we can't use the functions provided by GLFW. //

	///////////////////////////////////         GLFW DOCS :        //////////////////////////////////////////
	//																									   //
	//	There are a number of hints that can be set before the creation of a windowand context.            //
	//	Some affect the window itself, others affect the framebuffer or context.                           //
	//	These hints are set to their default values each time the library is initialized with glfwInit().  //
	//																									   //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _context_version_major);                 // Major.minor version make up the 3.3 of the,                   //
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _context_version_minor);                 // openGL version we want glfw to use.                           //
	glfwWindowHint(GLFW_OPENGL_PROFILE, _opengl_profile); // CORE profile is use to tell glfw we want to use modern openGL //

	_window = glfwCreateWindow(800, 600, _title, NULL, NULL); // glfwCeateWindow() takes width, height, title, monitor and share,    //
																				// width and height make up the dimesions of the window,               //
																				// montor determins the monitor to fill up when rendering full screen, //
																				// share takes anoter window context to share buffers, ect. with.      //

	if (_window == NULL) // glfwCreateWindow() returns NULL is anything failed when init the context. //
	{
		std::cout << "GLFW : Failed to create window" << std::endl;
		glfwTerminate();
		throw std::runtime_error("GLFW : Failed to create window");
	}

	glfwMakeContextCurrent(_window); // Select window as current rendering context, any changes to context will now be applied to window. //

	glewInit();

	glViewport(0, 0, 800, 600); // glviewport takes x, y, width, height where width and,            //
								// height define the size of the viewport coordinate axis,          //
								// and where x and y define the value of the lower left coordinate, //
								// changing these offsets the viewport coordinate axis.             //
}