#include "AnimationControllerManager.h"

#include "ArchiveStructures.h"
#include "AnimationControllerNode.h"
#include "AnimationController.h"
#include "Animation.h"
#include "Keyframe.h"
#include "Transform.h"
#include <assert.h>
#include <string.h>
#include <Math\MathEngine.h>

void AnimationControllerManager::AddAnimationController(AnimationController* const animController) {
	Add(new AnimationControllerNode(animController));
}

void AnimationControllerManager::RemoveAnimationController(const char* name) {
	Remove(Find(name));
}

AnimationController* AnimationControllerManager::FindAnimationController(const char* name) {
	AnimationController* animController = nullptr;
	AnimationControllerNode* animControllerNode = Find(name);
	if(animControllerNode) {
		animController = animControllerNode->getData();
	}
	return animController;
}

AnimationControllerNode* AnimationControllerManager::Find(const char* name) {
	AnimationControllerNode* animControllerNode = nullptr;
	if(name) {
		AnimationControllerNode* root = static_cast<AnimationControllerNode*>(GetObjectList()->getRoot());

		if(root) {
			animControllerNode = static_cast<AnimationControllerManager*>(GetInstance())->findDepthFirst(root, name);
		}
	}
	return animControllerNode;
}

void AnimationControllerManager::LoadAnimationsFromBuffer(const char* controllerName, const AnimationHeader& animationHeader, char* buffer) {
	AddAnimationController(loadAnimationsFromBuffer(controllerName, animationHeader, buffer));
}

AnimationControllerNode* AnimationControllerManager::findDepthFirst(AnimationControllerNode* const walker, const char* name) const {
	AnimationControllerNode* animControllerNode = nullptr;
	if(strcmp(name, walker->getName())) {
		animControllerNode = walker;
	} else {
		if(walker->getChild()) {
			animControllerNode = this->findDepthFirst(static_cast<AnimationControllerNode*>(walker->getChild()), name);
		}
		if(!animControllerNode && walker->getSibling()) {
			animControllerNode = this->findDepthFirst(static_cast<AnimationControllerNode*>(walker->getSibling()), name);
		}
	}
	return animControllerNode;
}

AnimationController* AnimationControllerManager::loadAnimationsFromBuffer(const char* controllerName, const AnimationHeader& animationHeader, char* buffer) {
	printf("      Loading animations...\n");
	AnimationController* animController = new AnimationController(controllerName);
	char* ptr = buffer;

	// Set up animations
	for(int animIndex = 0; animIndex < animationHeader.numAnimations; animIndex++) {
		Animation* animation = new Animation();
		animation->setName(ptr);
		ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +16);
		animation->setNumKeyframes(*reinterpret_cast<int*>(ptr));
		ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) + sizeof(ptr) +sizeof(int));

		// Increment ptr to keyframe location, set up keyframes
		Keyframe* keyframes = new Keyframe[animation->getNumKeyframes()];
		for(int keyframeIndex = 0; keyframeIndex < animation->getNumKeyframes(); keyframeIndex++) {
			Keyframe& keyframe = keyframes[keyframeIndex];
			keyframe.setTime(*reinterpret_cast<float*>(ptr));
			ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +sizeof(float));
			keyframe.setNumTransforms(*reinterpret_cast<int*>(ptr));

			// Increment ptr to transform data location, set up transforms
			Transform* transforms = new Transform[keyframe.getNumTransforms()];
			ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +sizeof(float) + sizeof(int));
			for(int transformIndex = 0; transformIndex < keyframe.getNumTransforms(); transformIndex++) {
				Transform& transform = transforms[transformIndex];
				TransformData* buffTransform = reinterpret_cast<TransformData*>(ptr);

				Vector buffTrans = buffTransform->translation;
				transform.setTranslation(new Vect(buffTrans.x, buffTrans.y, buffTrans.z));

				Quaternion buffRot = buffTransform->rotation;
				transform.setRotation(new Quat(buffRot.x, buffRot.y, buffRot.z, buffRot.w));

				Vector buffScale = buffTransform->scale;
				transform.setScale(new Vect(buffScale.x, buffScale.y, buffScale.z));

				// Increment ptr to next transform location
				ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +sizeof(TransformData));
			}
			keyframe.setTransforms(transforms);
		}
		animation->setKeyframes(keyframes);
		animController->AddAnimation(animation);
	}
	return animController;
}