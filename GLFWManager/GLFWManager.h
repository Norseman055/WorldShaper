#pragma once

#include "Singleton.h"

#define GLEW_STATIC
#include <glew\glew.h>
#include <GLFW\glfw3.h>

class GLFWManager : public Singleton<GLFWManager> {
	friend class Singleton<GLFWManager>;
public:
	// Methods
	static void Startup();
	static void Shutdown();

	static GLFWwindow* GetWindow();

	// Destructor (virtual just in case)
	virtual ~GLFWManager();

private:
	// Methods
	static void error_callback( int error, const char* description );
	static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods );

	// Private constructor
	GLFWManager();

	// Member variables
	GLFWwindow* mWindow;
};