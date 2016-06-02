#pragma once;

#include <vector>

struct Vector {
	float x, y, z;
};

struct ArchiveMatrix {
	float elements[4][4];
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

struct ArchiveKeyframe {
	float time;
	unsigned int numTransforms;
	std::vector<TransformData> boneTransforms;
};

struct ArchiveAnimation {
	char animName[16];
	unsigned int numKeyframes;
	std::vector<ArchiveKeyframe> keyframes;
};

struct SkinInfluence {
	unsigned int boneIndex;
	float weight;
};

struct SkinArray {
	SkinInfluence skinWeights[4];
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

struct BindPoseHeader {
	int numMatrices;
	int dataSize;
};

struct AnimationHeader {
	int numAnimations;
	int dataSize;
};

struct SkinningHeader {
	int numInfluenceVectors;
	int dataSize;
};