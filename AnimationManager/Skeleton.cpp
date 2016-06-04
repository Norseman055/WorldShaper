#include "Skeleton.h"

#include "PlaybackControls.h"
#include "AnimationController.h"

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

void Skeleton::setAnimationPlayback(const PlaybackControl control) {
	this->animations->setAnimationPlayback(control);
}

void Skeleton::setCurrentAnimation(const char* animName) {
	this->animations->setCurrentAnimation(animName);
}

void Skeleton::updateAnimation(const float gametime) const {
	this->animations->updateAnimation(gametime);
}

void Skeleton::removeAnimations() {
	this->animations = nullptr;
}

AnimationController* Skeleton::getAnimations() const {
	return this->animations;
}

void Skeleton::addBindPose(Matrix* const bindPose) {
	this->bindPose = bindPose;
}

Matrix* Skeleton::getBindPose() const {
	return this->bindPose;
}

void Skeleton::addSkinInfluence(SkinArray* const skinInfluence) {
	this->skinInfluence = skinInfluence;
}

SkinArray* Skeleton::getSkinInfluence() const {
	return this->skinInfluence;
}

int Skeleton::getNumLevels() const {
	return this->numLevels;
}

void Skeleton::setNumLevels(const int numLevels) {
	this->numLevels = numLevels;
}

Skeleton::Skeleton(const char* inName)
	: bones(nullptr), animations(nullptr), bindPose(nullptr), skinInfluence(nullptr), numBones(0), numLevels(0) {
	assert(inName);
	int nameLen = strlen(inName);
	this->name = new char[nameLen + 1];
	strcpy(this->name, inName);
}

Skeleton::~Skeleton() { }