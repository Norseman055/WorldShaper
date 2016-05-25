#pragma once;

struct Vector {
	float x, y, z;
};

struct Triangle {
	unsigned int a, b, c;
};

struct Bone {
	char boneName[32];
	int parentIndex;
	unsigned int level;
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

struct SkeletonHeader {
	int numBones;
	int dataSize;
};