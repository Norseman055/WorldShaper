#include "WorldShaper.h"

#include "GLFWManager\GLFWManager.h"
#include "ShaderManager\ShaderManager.h"
#include "ModelManager\ModelManager.h"
#include "TextureManager\TextureManager.h"
#include "GameObjectManager\GameObjectManager.h"
#include "CameraManager\CameraManager.h"
#include "AnimationManager\AnimationManager.h"
#include "ArchiveManager\ArchiveManager.h"

void WorldShaper::Run() {
	printf("===== Starting World Shaper Engine =====\n");
	WorldShaper* worldShaper = GetInstance();
	printf("===== World Shaper Engine started =====\n\n");

	Startup();
	GLFWwindow* window = GLFWManager::GetWindow();
	while(!glfwWindowShouldClose(window)) {
		// Core game loop, run until game completion
		worldShaper->update(glfwGetTime());
		worldShaper->draw();
	}
	Shutdown();
}

void WorldShaper::Startup() {
	GLFWManager::Startup();
	ShaderManager::Startup();
	TextureManager::Startup();
	ModelManager::Startup();
	AnimationManager::Startup();
	ArchiveManager::Startup();
	GameObjectManager::Startup();
	CameraManager::Startup();

	SetGLFWCallbacks();
}

void WorldShaper::SetGLFWCallbacks() {
	// Set callback for keyboard input
	glfwSetKeyCallback(GLFWManager::GetWindow(), GLFWManager::InputCallback);
	// Set callback for resize of window
	glfwSetFramebufferSizeCallback(GLFWManager::GetWindow(), CameraManager::FramebufferResizeCallback);
}

void WorldShaper::Shutdown() {
	CameraManager::Shutdown();
	GameObjectManager::Shutdown();
	ArchiveManager::Shutdown();
	AnimationManager::Shutdown();
	ModelManager::Shutdown();
	TextureManager::Shutdown();
	ShaderManager::Shutdown();
	GLFWManager::Shutdown();
}

void WorldShaper::update(double gameTime) {
	GameObjectManager::Update(gameTime);
}

void WorldShaper::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Update camera for consistency
	CameraManager::UpdateActiveCamera();

	// Draw Game Objects
	GameObjectManager::Draw(CameraManager::GetActiveCamera());

	// Swap buffers and poll for key events
	glfwSwapBuffers(GLFWManager::GetWindow());
	glfwPollEvents();
}

WorldShaper::~WorldShaper() { }