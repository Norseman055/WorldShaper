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

	static void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	// Destructor (virtual just in case)
	virtual ~GLFWManager();

private:
	// Methods
	static void ErrorCallback(int error, const char* description);

	// Private constructor
	GLFWManager();

	// Member variables
	GLFWwindow* mWindow;
};