#include "Pyramid.h"

#include "Vertex.h"
#include <stdio.h>

Pyramid::Pyramid()
	: Model(ModelType::Model_Pyramid) {
	printf("PYRAMID: Loading pyramid...\n");

	this->numVertices = 5;
	this->vertices = new Vertex[numVertices];

	vertices[0].pos = Vect(0.0f, 0.0f, 0.0f);
	vertices[1].pos = Vect(1.0f, -1.0f, 1.0f);
	vertices[2].pos = Vect(1.0f, -1.0f, -1.0f);
	vertices[3].pos = Vect(-1.0f, -1.0f, 1.0f);
	vertices[4].pos = Vect(-1.0f, -1.0f, -1.0f);
	vertices[0].normal = Vect(0.0f, 0.0f, 1.0f);
	vertices[1].normal = Vect(0.0f, 0.0f, 1.0f);
	vertices[2].normal = Vect(0.0f, 0.0f, 1.0f);
	vertices[3].normal = Vect(0.0f, 0.0f, 1.0f);
	vertices[4].normal = Vect(0.0f, 0.0f, 1.0f);
	vertices[0].color = Vect(1, 1, 1);
	vertices[1].color = Vect(1, 1, 1);
	vertices[2].color = Vect(1, 1, 1);
	vertices[3].color = Vect(1, 1, 1);
	vertices[4].color = Vect(1, 1, 1);
	vertices[0].uv = Vect(0.0f, 0.0f, 0.0f);
	vertices[1].uv = Vect(0.0f, 0.0f, 0.0f);
	vertices[2].uv = Vect(0.0f, 0.0f, 0.0f);
	vertices[3].uv = Vect(0.0f, 0.0f, 0.0f);
	vertices[4].uv = Vect(0.0f, 0.0f, 0.0f);

	this->numFaces = 4 * 3;
	this->faces = new int[numFaces];
	faces[0] = 0;
	faces[1] = 1;
	faces[2] = 2;
	faces[3] = 0;
	faces[4] = 3;
	faces[5] = 1;
	faces[6] = 0;
	faces[7] = 4;
	faces[8] = 3;
	faces[9] = 0;
	faces[10] = 2;
	faces[11] = 4;

	this->setupOpenGLBuffers();
}