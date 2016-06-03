#include "Keyframe.h"

#include "Transform.h"
#include <Math/MathEngine.h>

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

/*
 * Used to update a keyframe by interpolating between two other keyframes based on an time frame between the two
 */
void Keyframe::interpolate(const Keyframe& prev, const Keyframe& next, const float sTime) {
	Vect T, S;
	Quat R;
	for(int i = 0; i < prev.numTransforms; i++) {
		VectApp::Lerp(T, *prev.transforms[i].getTranslation(), *next.transforms[i].getTranslation(), sTime);
		QuatApp::Slerp(R, *prev.transforms[i].getRotation(), *next.transforms[i].getRotation(), sTime);
		VectApp::Lerp(S, *prev.transforms[i].getScale(), *next.transforms[i].getScale(), sTime);

		this->transforms[i].setTranslation(&T);
		this->transforms[i].setRotation(&R);
		this->transforms[i].setScale(&S);
	}
}

Keyframe::Keyframe()
	: time(0.0f), numTransforms(0), transforms(nullptr) { }

Keyframe::Keyframe(const float inTime, const int inNumTransforms)
	: time(inTime), numTransforms(inNumTransforms) {
	this->transforms = new Transform[numTransforms];
}

Keyframe::~Keyframe() {
	if(transforms) {
		delete[] transforms;
	}
}