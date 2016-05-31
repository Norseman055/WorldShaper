#include "Skeleton.h"

#include <PCSTree\PCSTree.h>
#include <assert.h>
#include <string.h>

const char* Skeleton::getName() const {
	return this->name;
}

PCSTree* Skeleton::getBones() const {
	return this->bones;
}

void Skeleton::setBones(PCSTree* const inBones) {
	this->bones = inBones;
}

void Skeleton::addAnimations(AnimationController* const animations) {
	this->animations = animations;
}

void Skeleton::removeAnimations() {
	this->animations = nullptr;
}

AnimationController* Skeleton::getAnimations() const {
	return this->animations;
}

int Skeleton::getNumLevels() const {
	return this->numLevels;
}

void Skeleton::setNumLevels(const int numLevels) {
	this->numLevels = numLevels;
}

Skeleton::Skeleton(const char* inName) 
	: bones(nullptr), animations(nullptr), numBones(0), numLevels(0)
{
	assert(inName);
	int nameLen = strlen(inName);
	this->name = new char[nameLen + 1];
	strcpy(this->name, inName);
}

Skeleton::~Skeleton() { }