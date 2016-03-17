#pragma once

#include "ModelTypes.h"

struct Vertex;

class Model {
public:
	ModelType getType() const;

	Vertex* getVertices() const;
	int getNumVertices() const;

	int* getFaces() const;
	int getNumFaces() const;

	Model( const ModelType );
	virtual ~Model() = 0;

protected:
	void setupOpenGLBuffers();

	ModelType type;

	unsigned int vao;
	unsigned int vboVertices;
	unsigned int vboFaces;
	
	Vertex* vertices;
	int numVertices;

	int* faces;
	int numFaces;
};