#include "WorldShaper.h"
#include "Macros.h"

#include "GLFWManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "GameObjectManager.h"

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
	ModelManager::Startup();
	TextureManager::Startup();
	GameObjectManager::Startup();
}

void WorldShaper::Shutdown() {
	GameObjectManager::Shutdown();
	TextureManager::Shutdown();
	ModelManager::Shutdown();
	GLFWManager::ShutdownGLFW();
}

void WorldShaper::update(double gameTime) {
	// Add update logic
	UNUSED( gameTime );
}

void WorldShaper::draw() {	
	float ratio;
	int width, height;

	// Get aspect ratio
	glfwGetFramebufferSize( GLFWManager::GetWindow(), &width, &height );
	ratio = width / ( float ) height;

	// Set viewport and clear the background
	glViewport( 0, 0, width, height );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Set the projection matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -ratio, ratio, -1.f, 1.f, 1.f, -1.f );
	glMatrixMode( GL_MODELVIEW );

	// Make a rotation matrix
	glLoadIdentity();
	glRotatef( ( float ) glfwGetTime() * 50.f, 0.f, 0.f, 1.f );

	// Create our triangle
	glBegin( GL_TRIANGLES );
	glColor3f( 1.f, 0.f, 0.f );
	glVertex3f( -0.6f, -0.4f, 0.f );
	glColor3f( 0.f, 1.f, 0.f );
	glVertex3f( 0.6f, -0.4f, 0.f );
	glColor3f( 0.f, 0.f, 1.f );
	glVertex3f( 0.f, 0.6f, 0.f );
	glEnd();

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