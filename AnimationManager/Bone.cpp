#include "Bone.h"

#include <assert.h>
#include <string.h>

#include <Math\MathEngine.h>

#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"

#include "Animation.h"
#include "Keyframe.h"
#include "Transform.h"

#define GLEW_STATIC
#include <glew\glew.h>
#include <GLFW\glfw3.h>

char* Bone::getName() const {
	return this->name;
}

void Bone::setBoneOrientation(Matrix* const orientation) {
	this->boneOrientation->set(*orientation);
}

void Bone::transform(Animation* const animation) {
	assert(animation);
	Matrix parentWorld;

	// get parent worldview
	if(!this->getParent()) {
		parentWorld.set(IDENTITY);
	} else {
		Bone* parentObj = static_cast<Bone*>(this->getParent());
		parentWorld = *parentObj->world;
	}

	// get bone data for scale, rotation, and translation
	Keyframe* tmp = animation->getResult();
	assert(tmp);

	Transform* bResult = tmp->getTransforms();
	assert(bResult);

	Matrix S = Matrix(SCALE, *bResult[index].getScale());
	Quat R = *bResult[index].getRotation();
	Matrix T = Matrix(TRANS, *bResult[index].getTranslation());

	Matrix M = S * R * T;

	// set local and world matrices
	this->local->set(M);
	this->world->set(*this->local * parentWorld);
}

void Bone::draw(Camera* const camera) const {
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
	glUniformMatrix4fv(modelMatrixLoc, 1, false, *this->boneOrientation);
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

Bone::Bone(const char* inName)
	: GO_Pyramid(inName), index(0), parentIndex(0), level(0) {
	assert(inName);
	int nameLen = strlen(inName);
	this->name = new char[nameLen + 1];
	strcpy(this->name, inName);

	this->boneOrientation = new Matrix(IDENTITY);
}

Bone::~Bone() { }