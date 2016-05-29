#include "Skeleton.h"

#include "AnimationController.h"
#include "Animation.h"
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

void Skeleton::addAnimation(Animation* const animation) {
	this->animations->AddAnimation(animation);
}

void Skeleton::removeAnimation(Animation* const animation) {
	this->animations->RemoveAnimation(animation);
}

Animation* Skeleton::find(const char* name) const {
	return this->animations->FindAnimation(name);
}

int Skeleton::getNumLevels() const {
	return this->numLevels;
}

void Skeleton::setNumLevels(const int numLevels) {
	this->numLevels = numLevels;
}

Skeleton::Skeleton(const char* inName) 
	: bones(nullptr), numBones(0), numLevels(0)
{
	assert(inName);
	int nameLen = strlen(inName);
	this->name = new char[nameLen + 1];
	strcpy(this->name, inName);

	this->animations = new AnimationController(this->name);
}

Skeleton::~Skeleton() { }