#include "AnimationController.h"

#include "Animation.h"
#include "PlaybackControls.h"
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

void AnimationController::setAnimationPlayback(const PlaybackControl control) {
	this->playbackControl = control;
}

void AnimationController::setCurrentAnimation(const char* name) {
	this->currentAnimation = findAnimation(name);
}

/*
 * Update animations
 * NOTE: gametime variable is the time that has passed since the last update.
 *		 IT IS NOT THE CURRENT GAME TIME.
 */
void AnimationController::updateAnimation(const float gametime) {
	this->switchTime(gametime);
	this->currentAnimation->update(this->tCurrent);
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

Animation* AnimationController::getCurrentAnimation() const {
	return this->currentAnimation;
}

void AnimationController::switchTime(const float deltaTime) {
	const float maxTime = this->currentAnimation->getMaxTime();
	switch(this->playbackControl) {
		case PlaybackControl::PLAY:
			this->tCurrent += deltaTime;
			if(this->tCurrent < 0.0f) {
				this->tCurrent = maxTime;
			} else if(this->tCurrent > maxTime) {
				this->tCurrent = maxTime;
			}
			break;
		case PlaybackControl::PLAY_LOOP:
			this->tCurrent += deltaTime;
			if(this->tCurrent < 0.0f) {
				this->tCurrent = maxTime;
			} else if(this->tCurrent > maxTime) {
				this->tCurrent = 0.0f;
			}
			break;
		case PlaybackControl::REWIND:
			this->tCurrent -= deltaTime;
			if(this->tCurrent < 0.0f) {
				this->tCurrent = 0.0f;
			} else if(this->tCurrent > maxTime) {
				this->tCurrent = maxTime;
			}
			break;
		case PlaybackControl::REWIND_LOOP:
			this->tCurrent -= deltaTime;
			if(this->tCurrent < 0.0f) {
				this->tCurrent = maxTime;
			} else if(this->tCurrent > maxTime) {
				this->tCurrent = maxTime;
			}
			break;
		default:
			// PAUSE, DO NOT CHANGE CURRENT ANIMATION TIME
			break;
	}
}

AnimationController::AnimationController(const char* inName)
	: currentAnimation(nullptr), playbackControl(PlaybackControl::PAUSE), tCurrent(0.0f) {
	assert(inName);
	int nameLen = strlen(inName);
	this->skeletonName = new char[nameLen + 1];
	strcpy(this->skeletonName, inName);
}

AnimationController::~AnimationController() { }