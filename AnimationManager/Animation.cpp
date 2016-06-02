#include "Animation.h"

#include "ArchiveStructures.h"
#include "Keyframe.h"
#include <assert.h>

const char* Animation::getName() const {
	return this->name;
}

void Animation::setName(const char* inName) {
	assert(inName);
	int nameLen = strlen(inName);
	this->name = new char[nameLen + 1];
	strcpy(this->name, inName);
}

int Animation::getNumKeyframes() const {
	return this->numKeyframes;
}

void Animation::setNumKeyframes(const int numKeyframes) {
	this->numKeyframes = numKeyframes;
}

Keyframe* const Animation::getKeyframes() const {
	return this->keyframes;
}

void Animation::setKeyframes(Keyframe* const keyframeTree) {
	this->keyframes = keyframeTree;
}

Animation::Animation()
	: name(nullptr), numKeyframes(0), keyframes(nullptr) { }

Animation::~Animation() {
	if(keyframes) {
		delete[] keyframes;
	}
}