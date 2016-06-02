#include "AnimationController.h"

#include "Animation.h"
#include <assert.h>
#include <string>

const char* AnimationController::getName() const {
	return this->skeletonName;
}

void AnimationController::AddAnimation(Animation* const animation) {
	animations.push_back(animation);
	if(!currentAnimation) {
		currentAnimation = animation;
	}
}

void AnimationController::RemoveAnimation(Animation* const animation) {
	animations.remove(animation);
}

Animation* AnimationController::FindAnimation(const char* name) const {
	Animation* retAnimation = nullptr;
	for(Animation* animation : animations) {
		if(strcmp(animation->getName(), name) == 0) {
			retAnimation = animation;
		}
	}
	return retAnimation;
}

AnimationController::AnimationController(const char* inName)
	: currentAnimation(nullptr) {
	assert(inName);
	int nameLen = strlen(inName);
	this->skeletonName = new char[nameLen + 1];
	strcpy(this->skeletonName, inName);
}

AnimationController::~AnimationController() { }