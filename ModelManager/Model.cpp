#include "Model.h"

#include "Math\MathEngine.h"

#include "Vertex.h"
#include <stdio.h>

#define GLEW_STATIC
#include <glew\glew.h>
#include <GLFW\glfw3.h>

ModelType Model::getType() const {
	return this->type;
}

unsigned int Model::getVao() const {
	return this->vao;
}

unsigned int Model::getVboVerts() const {
	return this->vboVertices;
}

unsigned int Model::getVboFaces() const {
	return this->vboFaces;
}

Vertex* Model::getVertices() const {
	return this->vertices;
}

int Model::getNumVertices() const {
	return this->numVertices;
}

int* Model::getFaces() const {
	return this->faces;
}

int Model::getNumFaces() const {
	return this->numFaces;
}

Matrix* Model::getModelMatrix() const {
	return this->modelMatrix;
}

void Model::setupOpenGLBuffers() {
	printf( "      Setting OpenGL buffers for model...\n" );
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	glGenBuffers( 1, &vboVertices );
	glBindBuffer( GL_ARRAY_BUFFER, vboVertices );
	glBufferData( GL_ARRAY_BUFFER, this->numVertices * sizeof( Vertex ), this->vertices, GL_STATIC_DRAW );

	glGenBuffers( 1, &vboFaces );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vboFaces );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->numFaces * sizeof( int ), this->faces, GL_STATIC_DRAW );
}

Model::Model(const ModelType inType)
	: type(inType), vao(0), vboVertices(0), vboFaces(0),
	vertices(nullptr), numVertices(0), faces(nullptr), numFaces(0) {
	this->modelMatrix = new Matrix(IDENTITY);
}

Model::~Model() { }