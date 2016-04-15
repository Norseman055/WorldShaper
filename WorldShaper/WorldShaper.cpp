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

	// Setup GLFW window and viewport, clear background
	int width, height;

	glfwGetFramebufferSize( GLFWManager::GetWindow(), &width, &height );
	glViewport( 0, 0, width, height );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Set the projection matrix
	// UPDATE TO USE CAMERA PROJECTION MATRIX
	float ratio = width / ( float ) height;
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -ratio, ratio, -1.f, 1.f, 1.f, -1.f );
	glMatrixMode( GL_MODELVIEW );

	// Draw triangle
	glLoadIdentity();
	glRotatef( ( float ) glfwGetTime() * 50.f, 0.f, 0.f, 1.f );
	
	glBegin( GL_TRIANGLES );
	glColor3f( 1.f, 0.f, 0.f );
	glVertex3f( -0.6f, -0.4f, 0.f );
	glColor3f( 0.f, 1.f, 0.f );
	glVertex3f( 0.6f, -0.4f, 0.f );
	glColor3f( 0.f, 0.f, 1.f );
	glVertex3f( 0.f, 0.6f, 0.f );
	glEnd();

	// Draw Game Objects
	GameObjectManager::Draw();

	// Swap buffers and poll for key events
	glfwSwapBuffers( GLFWManager::GetWindow() );
	glfwPollEvents();
}

WorldShaper::~WorldShaper() { }