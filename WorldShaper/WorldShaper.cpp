#include "WorldShaper.h"

#include "GLFWManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "CameraManager.h"

void WorldShaper::Run() {
	Startup();
	auto window = GLFWManager::GetWindow();
	while ( !glfwWindowShouldClose(window)) {
		// Core game loop, run until game completion
		getInstance()->update( glfwGetTime() );
		getInstance()->draw();
	}
	Shutdown();
}

void WorldShaper::Startup() {
	GLFWManager::StartupGLFW();
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
	GLFWManager::ShutdownGLFW();
}

void WorldShaper::update(double gameTime) {
	// Add update logic
	ModelManager::Update( gameTime );
	GameObjectManager::Update( gameTime );
}

void WorldShaper::draw() {

	// Setup GLFW window and viewport, clear background
	int width, height;

	glfwGetFramebufferSize( GLFWManager::GetWindow(), &width, &height );
	float ratio = width / ( float ) height;
	glViewport( 0, 0, width, height );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Set the projection matrix
	// UPDATE TO USE CAMERA PROJECTION MATRIX
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -ratio, ratio, -1.f, 1.f, 1.f, -1.f );
	glMatrixMode( GL_MODELVIEW );

	// Draw Game Objects
	GameObjectManager::Draw();

	// Swap buffers and poll for key events
	glfwSwapBuffers( GLFWManager::GetWindow() );
	glfwPollEvents();
}

WorldShaper* WorldShaper::getInstance() {
	static WorldShaper instance;
	return &instance;
}

WorldShaper::WorldShaper() { }

WorldShaper::~WorldShaper() { }