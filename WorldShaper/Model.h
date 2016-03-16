#pragma once

#include "ModelTypes.h"
#include "Vertex.h"
#include "GLFWManager.h"

class Model {
public:
	ModelType getType() const {
		return this->type;
	}

	Vertex* getVertices() const {
		return this->vertices;
	}
	int getNumVertices() const {
		return this->numVertices;
	}

	int* getFaces() const {
		return this->faces;
	}
	int getNumFaces() const {
		return this->numFaces;
	}

	Model( ModelType inType )
		: type( inType ),
		vao( 0 ), vboVertices( 0 ), vboFaces( 0 ),
		vertices( nullptr ), numVertices( 0 ),
		faces( nullptr ), numFaces( 0 ) 
	{ }

	virtual ~Model() = 0;

protected:
	void setupOpenGLBuffers() {
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

	ModelType type;

	unsigned int vao;
	unsigned int vboVertices;
	unsigned int vboFaces;
	
	Vertex* vertices;
	int numVertices;

	int* faces;
	int numFaces;
};

inline Model::~Model() { }