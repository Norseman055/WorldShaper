#include "Keyframe.h"

#include "Transform.h"

float Keyframe::getTime() const {
	return this->time;
}

void Keyframe::setTime(const float time) {
	this->time = time;
}

int Keyframe::getNumTransforms() const {
	return this->numTransforms;
}

void Keyframe::setNumTransforms(const int numTransforms) {
	this->numTransforms = numTransforms;
}

Transform* Keyframe::getTransforms() const {
	return this->transforms;
}

void Keyframe::setTransforms(Transform* const transforms) {
	this->transforms = transforms;
}

Keyframe::Keyframe()
	: time(0.0f), numTransforms(0), transforms(nullptr) { }

Keyframe::~Keyframe() { 
	if(transforms) {
		delete[] transforms;
	}
}