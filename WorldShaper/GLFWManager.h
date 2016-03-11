#pragma once

#define GLEW_STATIC
#include <glew\glew.h>
#include <GLFW\glfw3.h>

class GLFWManager {
public:
	// Methods
	static void StartupGLFW();
	static void ShutdownGLFW();

	static GLFWwindow* GetWindow();

	// Destructor (virtual just in case)
	virtual ~GLFWManager();

private:
	// Methods
	static void error_callback( int error, const char* description );
	static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods );

	// Singleton methods
	static GLFWManager* getInstance();
	GLFWManager();

	// Member variables
	GLFWwindow* mWindow;
};