#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Vector {
	float x, y, z;
};

struct Triangle {
	unsigned int a, b, c;
};

struct ModelFileHeader {
	char modelName[24];
	int sizeofModelData;
};

struct VerticesHeader {
	int numVertices;
	int dataSize;
};

struct NormalHeader {
	int numNormals;
	int dataSize;
};

struct TriangleHeader {
	int numTriangles;
	int dataSize;
};

#endif