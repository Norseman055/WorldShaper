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
	this->result = this->keyframes;
}

Keyframe* const Animation::getResult() const {
	return this->result;
}

float Animation::getMaxTime() const {
	float returnTime;
	if(this->keyframes && this->numKeyframes != 0) {
		returnTime = this->keyframes[this->numKeyframes - 1].getTime();
	} else {
		returnTime = 0.0f;
	}
	return returnTime;
}

void Animation::getBoundingKeyframes(const float keyTime, Keyframe*& previous, Keyframe*& next) const {
	if(keyTime >= 0.0f) {
		next = &this->keyframes[1];
		for(int i = 1; i < this->numKeyframes; i++) {
			if(keyTime >= this->keyframes[i].getTime()) {
				next = &this->keyframes[i];
			} else {
				previous = &this->keyframes[i - 1];
				break;
			}
		}
	}
}

void Animation::update(const float keyframeTime) {
	Keyframe* prevKeyframe = this->keyframes;
	Keyframe* nextKeyframe = prevKeyframe;

	this->getBoundingKeyframes(keyframeTime, prevKeyframe, nextKeyframe);

	if(!this->result) {
		this->result = new Keyframe(keyframeTime, prevKeyframe->getNumTransforms());
	}
	const float sTime = (keyframeTime - prevKeyframe->getTime()) / (nextKeyframe->getTime() - prevKeyframe->getTime());
	this->result->interpolate(prevKeyframe, nextKeyframe, sTime);
}

Animation::Animation()
	: name(nullptr), numKeyframes(0), keyframes(nullptr), result(nullptr) { }

Animation::~Animation() {
	if(keyframes) {
		delete[] keyframes;
	}
}