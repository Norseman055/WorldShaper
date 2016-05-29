#include "Transform.h"

#include <Math\MathEngine.h>

Vect* Transform::getTranslation() const {
	return this->translation;
}

void Transform::setTranslation(Vect* const translation) {
	this->translation = translation;
}

Quat* Transform::getRotation() const {
	return this->rotation;
}

void Transform::setRotation(Quat* const rotation) {
	this->rotation = rotation;
}

Vect* Transform::getScale() const {
	return this->scale;
}

void Transform::setScale(Vect* const scale) {
	this->scale = scale;
}

Transform::Transform()
	: translation(nullptr), rotation(nullptr), scale(nullptr)
{ }

Transform::~Transform() {
	delete translation;
	delete rotation;
	delete scale;
}