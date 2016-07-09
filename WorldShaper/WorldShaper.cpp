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
	printf("========== WORLD SHAPER : START ==========\n\n");
	WorldShaper* worldShaper = GetInstance();
	Startup();
	printf("========== WORLD SHAPER : FINISHED STARTING ==========\n\n");

	worldShaper->runGameLoop();
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

	// Set callbacks for GLFW
	SetGLFWCallbacks();
}

void WorldShaper::SetGLFWCallbacks() {
	// Set callback for keyboard input
	glfwSetKeyCallback(GLFWManager::GetWindow(), GLFWManager::InputCallback);
	// Set callback for resize of window
	glfwSetFramebufferSizeCallback(GLFWManager::GetWindow(), CameraManager::FramebufferResizeCallback);
}

void WorldShaper::Shutdown() {
	printf("========== WORLD SHAPER : EXITING ==========\n\n");
	CameraManager::Shutdown();
	GameObjectManager::Shutdown();
	ArchiveManager::Shutdown();
	AnimationManager::Shutdown();
	ModelManager::Shutdown();
	TextureManager::Shutdown();
	ShaderManager::Shutdown();
	GLFWManager::Shutdown();
}

void WorldShaper::runGameLoop() {
	printf("========== WORLD SHAPER : GAME LOOP START ==========\n\n");
	GLFWwindow* window = GLFWManager::GetWindow();
	while(!glfwWindowShouldClose(window)) {
		this->tCurrent = static_cast<float>(glfwGetTime());
		this->tDelta = this->tCurrent - this->tPrevious;

		// Game loop set to 60fps maximum
		if(tDelta > 0.1666f) {
			this->update(tDelta);
		}

		this->draw();

		this->tPrevious = this->tCurrent;
	}
}

void WorldShaper::update(const float gameTime) {
	GameObjectManager::Update(gameTime);
}

void WorldShaper::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Update camera for consistency
	CameraManager::UpdateActiveCamera();

	// Draw Game Objects
	GameObjectManager::Draw(CameraManager::GetActiveCamera());

	// Swap buffers and poll for key events
	glfwSwapBuffers(GLFWManager::GetWindow());
	glfwPollEvents();
}

WorldShaper::WorldShaper()
	: tCurrent(0.0f), tPrevious(0.0f), tDelta(0.0f) { }

WorldShaper::~WorldShaper() { }