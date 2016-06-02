#include "AnimationController.h"

#include "Animation.h"
#include <assert.h>
#include <string>

const char* AnimationController::getName() const {
	return this->skeletonName;
}

void AnimationController::addAnimation(Animation* const animation) {
	animations.push_back(animation);
	if(!currentAnimation) {
		currentAnimation = animation;
	}
}

void AnimationController::setCurrentAnimation(const char* name) {
	this->currentAnimation = findAnimation(name);
}

void AnimationController::updateAnimation(const float gametime) {
	float deltaTime = 0.0f;
	if(this->lastUpdateTime != 0.0f) {
		deltaTime = gametime - this->lastUpdateTime;
	}

	switch(this->playbackControl) {
		case PlaybackControl::PLAY:
			this->playAnimation(deltaTime);
			break;
		case PlaybackControl::REWIND:
			this->rewindAnimation(deltaTime);
			break;
		case PlaybackControl::LOOP:
			this->loopAnimation(deltaTime);
			break;
		default:
			// PAUSE, do nothing
			break;
	}
	this->lastUpdateTime = gametime;
}

void AnimationController::removeAnimation(Animation* const animation) {
	animations.remove(animation);
}

Animation* AnimationController::findAnimation(const char* name) const {
	Animation* retAnimation = nullptr;
	for(Animation* animation : animations) {
		if(strcmp(animation->getName(), name) == 0) {
			retAnimation = animation;
		}
	}
	return retAnimation;
}

void AnimationController::playAnimation(const float deltaTime) {
	_CRT_UNUSED(deltaTime);
}

void AnimationController::rewindAnimation(const float deltaTime) {
	_CRT_UNUSED(deltaTime);
}

void AnimationController::loopAnimation(const float deltaTime) {
	_CRT_UNUSED(deltaTime);
}

AnimationController::AnimationController(const char* inName)
	: currentAnimation(nullptr), playbackControl(PlaybackControl::PAUSE), lastUpdateTime(0.0f) {
	assert(inName);
	int nameLen = strlen(inName);
	this->skeletonName = new char[nameLen + 1];
	strcpy(this->skeletonName, inName);
}

AnimationController::~AnimationController() { }