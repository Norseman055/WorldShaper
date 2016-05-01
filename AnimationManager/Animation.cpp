#include "Animation.h"

const char* Animation::getName() const {
	return this->name;
}

Animation::Animation(const char* inName)
	: name(inName) { }

Animation::~Animation() { }