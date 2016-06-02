#pragma once

#include "ModelTypes.h"

struct Vertex;
class Matrix;

class Model {
public:
	ModelType getType() const;

	unsigned int getVao() const;
	unsigned int getVboVerts() const;
	unsigned int getVboFaces() const;

	Vertex* getVertices() const;
	void setVertices(Vertex* const);
	int getNumVertices() const;
	void setNumVertices(const int);

	int* getFaces() const;
	void setFaces(int* const);
	int getNumFaces() const;
	void setNumFaces(const int);

	void updateVbos();

	Matrix* getModelMatrix() const;

	Model(const ModelType);
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

	Matrix* modelMatrix;
};