#include "GO_Cube.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

void GO_Cube::setupCube() {
	this->setModel(ModelManager::FindModel(ModelType::Model_Cube));
	this->setTexture(TextureManager::FindTexture(TextureType::Texture_Brick));
	this->setShader(ShaderManager::FindShader(ShaderType::Shader_Phong));
}

GO_Cube::GO_Cube(const char* name)
	: GameObject(GameObjectType::GameObject_CubeBrick, name) {
	printf("GO_CUBE: Creating Cube - %s...\n", name);
	this->setupCube();
}

GO_Cube::~GO_Cube() { }