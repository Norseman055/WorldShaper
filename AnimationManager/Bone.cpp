#include "Bone.h"

#include <assert.h>
#include <string.h>

#include <Math\MathEngine.h>

#include "Animation.h"
#include "Keyframe.h"
#include "Transform.h"

char* Bone::getName() const {
	return this->name;
}

void Bone::setBoneOrientation(Matrix* const orientation) {
	this->boneOrientation->set(*orientation);
}

void Bone::transform(Animation* const animation) {
	assert(animation);
	Matrix parentWorld;

	// get parent worldview
	if(!this->getParent()) {
		parentWorld.set(IDENTITY);
	} else {
		Bone* parentObj = static_cast<Bone*>(this->getParent());
		parentWorld = *parentObj->world;
	}

	// get bone data for scale, rotation, and translation
	Keyframe* tmp = animation->getResult();
	assert(tmp);

	Transform* bResult = tmp->getTransforms();
	assert(bResult);

	Matrix S = Matrix(SCALE, *bResult[index].getScale());
	Quat R = *bResult[index].getRotation();
	Matrix T = Matrix(TRANS, *bResult[index].getTranslation());

	Matrix M = S * R * T;

	// set local and world matrices
	this->local->set(M);
	this->world->set(*this->local * parentWorld);
}

Bone::Bone(const char* inName)
	: GO_Pyramid(inName), index(0), parentIndex(0), level(0) {
	assert(inName);
	int nameLen = strlen(inName);
	this->name = new char[nameLen + 1];
	strcpy(this->name, inName);

	this->boneOrientation = new Matrix(IDENTITY);
}

Bone::~Bone() { }