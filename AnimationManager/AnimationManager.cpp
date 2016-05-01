#include "AnimationManager.h"
#include "Macros.h"

#include "AnimationNode.h"
#include "Animation.h"

#include <string.h>

void AnimationManager::Startup() {
	printf("\n===== Starting Animation Manager =====\n");
	GetInstance();
	LoadAnimations();
	printf("===== Animation Manager started =====\n\n");
}

void AnimationManager::Shutdown() {
	Cleanup();
	DestroyInstance();
}

void AnimationManager::AddAnimation(Animation* const animation) {
	Add(new AnimationNode(animation));
}

void AnimationManager::RemoveAnimation(const char* name) {
	Remove(Find(name));
}

Animation* AnimationManager::FindAnimation(const char* name) {
	Animation* animation = nullptr;
	AnimationNode* animationNode = Find(name);
	if(animationNode) {
		animation = animationNode->getData();
	}
	return animation;
}

void AnimationManager::LoadAnimations() {
	printf("  Loading animations...\n");
}

AnimationNode* AnimationManager::Find(const char* name) {
	AnimationNode* animation = nullptr;
	if(name) {
		AnimationNode* root = static_cast<AnimationNode*>(GetObjectList()->getRoot());

		if(root) {
			animation = static_cast<AnimationManager*>(GetInstance())->findDepthFirst(root, name);
		}
	}
	return animation;
}

AnimationNode* AnimationManager::findDepthFirst(AnimationNode* const walker, const char* name) const {
	AnimationNode* animation = nullptr;
	if(strcmp(name, walker->getName())) {
		animation = walker;
	} else {
		if(walker->getChild()) {
			animation = this->findDepthFirst(static_cast<AnimationNode*>(walker->getChild()), name);
		}
		if(!animation && walker->getSibling()) {
			animation = this->findDepthFirst(static_cast<AnimationNode*>(walker->getSibling()), name);
		}
	}
	return animation;
}