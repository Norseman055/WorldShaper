#include "Transform.h"

#include <Math\MathEngine.h>

Vect* Transform::getTranslation() const {
	return this->translation;
}

void Transform::setTranslation(const Vect* const translation) {
	this->translation->set(*translation);
}

Quat* Transform::getRotation() const {
	return this->rotation;
}

void Transform::setRotation(const Quat* const rotation) {
	this->rotation->set(*rotation);
}

Vect* Transform::getScale() const {
	return this->scale;
}

void Transform::setScale(const Vect* const scale) {
	this->scale->set(*scale);
}

Transform::Transform() {
	this->translation = new Vect;
	this->rotation = new Quat;
	this->scale = new Vect;
}

Transform::~Transform() {
	delete translation;
	delete rotation;
	delete scale;
}