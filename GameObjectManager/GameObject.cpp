#include "GameObject.h"
#include "Macros.h"

#include "Math\Matrix.h"

#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"

#include <stdio.h>

#define GLEW_STATIC
#include <glew\glew.h>
#include <GLFW\glfw3.h>

GameObjectType GameObject::getType() const {
	return this->type;
}

const char* GameObject::getName() const {
	return this->name;
}

void GameObject::setModel( Model* const inModel ) {
	printf( "      Setting model...\n" );
	this->model = inModel;
}

void GameObject::setTexture( Texture* const inTexture ) {
	printf( "      Setting texture...\n" );
	this->texture = inTexture;
}

void GameObject::setShader( Shader* const inShader ) {
	printf( "      Setting shader...\n" );
	this->shader = inShader;
}

void GameObject::update( const double gameTime ) const {
	// Add update logic here
	UNUSED( gameTime );
}

void GameObject::draw(Camera* const camera) const {
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

	glVertexAttribPointer(vertPosLoc, 4, GL_FLOAT, false, sizeof(Vertex), static_cast< void * >(nullptr));
	glEnableVertexAttribArray(vertPosLoc);

	glVertexAttribPointer(vertNormalLoc, 4, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast< void * >(sizeof(Vect)));
	glEnableVertexAttribArray(vertNormalLoc);

	glVertexAttribPointer(vertColorLoc, 4, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast< void * >(2 * sizeof(Vect)));
	glEnableVertexAttribArray(vertColorLoc);

	glVertexAttribPointer(uvLoc, 4, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast< void * >(3 * sizeof(Vect)));
	glEnableVertexAttribArray(uvLoc);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->model->getVboFaces());
	glDrawElements(GL_TRIANGLES, this->model->getNumFaces(), GL_UNSIGNED_INT, nullptr);
}

GameObject::GameObject( const GameObjectType inType, const char* inName )
	: type( inType ), name( inName ), model( nullptr ), texture( nullptr ), shader( nullptr ) {
	printf( "    Creating game object...\n" );
}

GameObject::~GameObject() { }