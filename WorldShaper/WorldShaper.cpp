#include "WorldShaper.h"

#include "GLFWManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "CameraManager.h"

void WorldShaper::Run() {
	printf( "===== Starting World Shaper Engine =====\n" );
	WorldShaper* worldShaper = GetInstance();
	printf( "===== World Shaper Engine started =====\n\n" );

	Startup();
	GLFWwindow* window = GLFWManager::GetWindow();
	while ( !glfwWindowShouldClose(window)) {
		// Core game loop, run until game completion
		worldShaper->update( glfwGetTime() );
		worldShaper->draw();
	}
	Shutdown();
}

void WorldShaper::Startup() {
	GLFWManager::Startup();
	ShaderManager::Startup();
	TextureManager::Startup();
	ModelManager::Startup();
	GameObjectManager::Startup();
	CameraManager::Startup();
}

void WorldShaper::Shutdown() {
	CameraManager::Shutdown();
	GameObjectManager::Shutdown();
	ModelManager::Shutdown();
	TextureManager::Shutdown();
	ShaderManager::Shutdown();
	GLFWManager::Shutdown();
}

void WorldShaper::update(double gameTime) {
	GameObjectManager::Update( gameTime );
}

void WorldShaper::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw Game Objects
	GameObjectManager::Draw(CameraManager::GetActiveCamera());

	// Swap buffers and poll for key events
	glfwSwapBuffers( GLFWManager::GetWindow() );
	glfwPollEvents();
}

WorldShaper::~WorldShaper() { }