#include "GO_Humanoid.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "SkeletonManager.h"

#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Skeleton.h"

#include "PlaybackControls.h"

#include <stdio.h>
#include <Math\Matrix.h>

#define GLEW_STATIC
#include <glew\glew.h>
#include <GLFW\glfw3.h>

void GO_Humanoid::setAnimation(const HumanoidAnim animation) {
	this->currAnim = animation;

	const char* animName;
	switch(animation) {
		case HumanoidAnim::Anim_Shot:
			animName = "shot";
			break;
		case HumanoidAnim::Anim_Punch:
			animName = "punch";
			break;
		case HumanoidAnim::Anim_Run:
			animName = "run";
			break;
		case HumanoidAnim::Anim_Take001:
			animName = "Take 001";
			break;
		default:
			// BIND POSE, do nothing
			animName = nullptr;
			break;
	}
	if(animName) {
		this->skeleton->setCurrentAnimation(animName);
	}
}

void GO_Humanoid::transform(Animation* const) { }

void GO_Humanoid::update(const float gametime) const {
	this->skeleton->updateAnimation(gametime);
}

void GO_Humanoid::draw(Camera* const camera) const {
	GLuint shaderProgram = this->shader->getShaderID();
	GLuint textureID = this->texture->getTextureID();

	Matrix viewMatrix(camera->getViewMatrix());
	Matrix projectionMatrix(camera->getProjectionMatrix());

	glUseProgram(shaderProgram);

	auto modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
	auto viewMatrixLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
	auto projectionMatrixLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");

	// Since the matrix class has an overloaded 'double *' operator to transparently
	// cast to a c-style array, we can easily send the matrix to OpenGL just by putting
	// the matrix object in the last parameter!
	glUniformMatrix4fv(modelMatrixLoc, 1, false, *this->model->getModelMatrix());
	glUniformMatrix4fv(viewMatrixLoc, 1, false, viewMatrix);
	glUniformMatrix4fv(projectionMatrixLoc, 1, false, projectionMatrix);

	auto cameraPosLoc = glGetUniformLocation(shaderProgram, "cameraPos");

	glUniform4f(cameraPosLoc, camera->getPosition()[x], camera->getPosition()[y], camera->getPosition()[z], camera->getPosition()[w]);

	auto specColorLoc = glGetUniformLocation(shaderProgram, "specularColor");
	auto shinyLoc = glGetUniformLocation(shaderProgram, "shininess");

	glUniform4f(specColorLoc, 1, 1, 1, 1);
	glUniform1f(shinyLoc, 50);

	// TEXTURES
	glBindTexture(GL_TEXTURE_2D, textureID);

	auto vertPosLoc = glGetAttribLocation(shaderProgram, "vertexPos");
	auto vertColorLoc = glGetAttribLocation(shaderProgram, "vertexColor");
	auto vertNormalLoc = glGetAttribLocation(shaderProgram, "vertexNormal");
	auto uvLoc = glGetAttribLocation(shaderProgram, "UV");

	glBindBuffer(GL_ARRAY_BUFFER, this->model->getVboVerts());

	glVertexAttribPointer(vertPosLoc, 4, GL_FLOAT, false, sizeof(Vertex), static_cast<void *>(nullptr));
	glEnableVertexAttribArray(vertPosLoc);

	glVertexAttribPointer(vertNormalLoc, 4, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void *>(sizeof(Vect)));
	glEnableVertexAttribArray(vertNormalLoc);

	glVertexAttribPointer(vertColorLoc, 4, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void *>(2 * sizeof(Vect)));
	glEnableVertexAttribArray(vertColorLoc);

	glVertexAttribPointer(uvLoc, 4, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void *>(3 * sizeof(Vect)));
	glEnableVertexAttribArray(uvLoc);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->model->getVboFaces());
	glDrawElements(GL_TRIANGLES, 3 * this->model->getNumFaces(), GL_UNSIGNED_INT, nullptr);
}

void GO_Humanoid::setupHumanoid() {
	this->setModel(ModelManager::FindModel(ModelType::Model_Generic));
	this->setTexture(TextureManager::FindTexture(TextureType::Texture_Brick));
	this->setShader(ShaderManager::FindShader(ShaderType::Shader_Phong));
	this->setSkeleton(SkeletonManager::FindSkeleton("humanoid2"));

	this->skeleton->setAnimationPlayback(PlaybackControl::PLAY);
	this->setAnimation(HumanoidAnim::Anim_Run);
}

GO_Humanoid::GO_Humanoid(const char* name)
	: GameObject(GameObjectType::GameObject_Generic, name), currAnim(HumanoidAnim::Anim_BindPose) {
	printf("GO_HUMANOID: Creating Humanoid - %s...\n", name);
	this->setupHumanoid();
}

GO_Humanoid::~GO_Humanoid() { }