#pragma once

#include <PCSTree\PCSNode.h>
#include "GO_Pyramid.h"

#define BONE_WIDTH 2.0f

class Matrix;

class Bone : public PCSNode, public GO_Pyramid {
public:
	char* getName() const;

	void setBoneOrientation(Matrix* const);

	void transform(Animation* const) override;

	Bone(const char*);
	virtual ~Bone();

private:
	char* name;
	Matrix* boneOrientation;
public:
	int index;
	int parentIndex;
	unsigned int level;
};