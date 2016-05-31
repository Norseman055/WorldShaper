/// This converter class and almost every method in it is written by Vitor Fernandes. While some modifications may
/// have been made to a few of the functions, the majority of these functions are either direct copies or very close copies
/// of his work. All credit goes to him for this converter and the functionality therein. It has been modified for use
/// with my game engine, but is in no way work attributable to me.

#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Vector {
	float x, y, z;
};

struct Quaternion {
	float x, y, z, w;
};

struct Triangle {
	unsigned int a, b, c;
};

struct Bone {
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
	unsigned int numTransforms;
	vector<TransformData> boneTransforms;
};

struct Animation {
	char animName[16];
	unsigned int numKeyframes;
	vector<Keyframe> keyframes;
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

#endif