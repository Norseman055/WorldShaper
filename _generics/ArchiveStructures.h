#pragma once;

#include <vector>

struct Vector {
	float x, y, z;
};

struct Quaternion {
	float x, y, z, w;
};

struct Triangle {
	unsigned int a, b, c;
};

struct ArchiveBone {
	char boneName[32];
	int parentIndex;
	int level;
};

struct TransformData {
	Quaternion rotation;
	Vector translation;
	Vector scale;
};

struct Keyframe {
	float time;
	int numTransforms;
	std::vector<TransformData> boneTransforms;
};

struct ArchiveAnimation {
	char animName[16];
	int numKeyframes;
	std::vector<Keyframe> keyframes;
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

struct AnimationHeader {
	int numAnimations;
	int dataSize;
};