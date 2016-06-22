#include "GO_Pyramid.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

void GO_Pyramid::setupPyramid() {
	this->setModel(ModelManager::FindModel(ModelType::Model_Pyramid));
	this->setTexture(TextureManager::FindTexture(TextureType::Texture_Brick));
	this->setShader(ShaderManager::FindShader(ShaderType::Shader_Phong));
}

GO_Pyramid::GO_Pyramid(const char* name)
	: GameObject(GameObjectType::GameObject_PyramidBrick, name) {
	printf("GO_PYRAMID: Creating Pyramid - %s...\n", name);
	this->setupPyramid();
}

GO_Pyramid::~GO_Pyramid() { }