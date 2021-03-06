#include "GLFWManager.h"

#include <stdlib.h>
#include <stdio.h>

#include "Macros.h"

void GLFWManager::Startup() {
	printf("===== Starting GLFW Manager =====\n");
	GLFWManager* glfwManager = GetInstance();

	// Set error callback prior to initialization to notify if initialization fails
	glfwSetErrorCallback(ErrorCallback);

	// Initialize GLFW library
	printf("  Initializing GLFW library...");
	if(!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	printf("  Success!\n");

	// Create a window and context, make a current OpenGL context
	printf("  Creating game window...");
	glfwManager->mWindow = glfwCreateWindow(GAME_WIDTH, GAME_HEIGHT, "WorldShaper - Make your own", nullptr, nullptr);
	if(!glfwManager->mWindow) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	printf("  Success!\n");
	printf("  Making OpenGL context current...");
	glfwMakeContextCurrent(glfwManager->mWindow);
	glfwSwapInterval(1);
	printf("  Success!\n");

	printf("  Initializing GLEW...");
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(err != GLEW_OK) {
		Shutdown();
		exit(EXIT_FAILURE);
	}
	printf("  Success!\n");
	printf("===== GLFW Manager started =====\n\n");

	// Display OpenGL version info
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// Enable OpenGL depth-testing
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void GLFWManager::Shutdown() {
	// Destroy game window
	glfwDestroyWindow(GetInstance()->mWindow);

	// Terminate GLFW
	glfwTerminate();
}

GLFWwindow* GLFWManager::GetWindow() {
	return GetInstance()->mWindow;
}

void GLFWManager::ErrorCallback(int error, const char* description) {
	UNUSED(error);

	fputs(description, stderr);
}

void GLFWManager::InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	UNUSED(window);
	UNUSED(scancode);
	UNUSED(mods);

	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(GetInstance()->mWindow, GL_TRUE);
	}
}

GLFWManager::GLFWManager()
	: mWindow(nullptr) { }

GLFWManager::~GLFWManager() { }