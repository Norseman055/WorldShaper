#include "AnimationManager.h"
#include "Macros.h"

#include "ArchiveStructures.h"
#include "AnimationNode.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Bone.h"

#include <assert.h>
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

void AnimationManager::LoadAnimationFromBuffer(ModelFileHeader& fileHeader, char* const buffer) {
	printf("  Loading animation data from buffer... \n");
	AnimationManager* instance = static_cast<AnimationManager*>(GetInstance());
	void* ptr = buffer;

	Skeleton* skeleton = new Skeleton(fileHeader.modelName);

	// Go to skeleton header
	VerticesHeader* verticesHeader = reinterpret_cast<VerticesHeader*>(ptr);
	ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(verticesHeader) + verticesHeader->dataSize);
	NormalHeader* normalHeader = reinterpret_cast<NormalHeader*>(ptr);
	ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(normalHeader) + normalHeader->dataSize);
	TriangleHeader* triangleHeader = reinterpret_cast<TriangleHeader*>(ptr);
	ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(triangleHeader) + triangleHeader->dataSize);

	// Load skeleton hierarchy
	printf("    Loading skeleton hierarchy from buffer...\n");
	SkeletonHeader* skeletonHeader = reinterpret_cast<SkeletonHeader*>(ptr);
	ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(skeletonHeader));
	instance->loadSkeletonFromBuffer(*skeleton, *skeletonHeader, ptr);

	// Load animations
	printf("    Loading animations from buffer...\n");
	ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) +skeletonHeader->dataSize);
	AnimationHeader* animationHeader = reinterpret_cast<AnimationHeader*>(ptr);
	ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(animationHeader));
	instance->loadAnimationsFromBuffer(*animationHeader, ptr);
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

void AnimationManager::loadSkeletonFromBuffer(Skeleton& skeleton, const SkeletonHeader& header, void* const buffer) {
	printf("      Loading %i bones...\n ", header.numBones);
	ArchiveBone* buffBones = reinterpret_cast<ArchiveBone*>(buffer);
	Bone** bonePointers = new Bone*[header.numBones];
	PCSTree* bones = skeleton.getBones();

	if(!bones) {
		bones = new PCSTree();
	}

	ArchiveBone& firstBone = buffBones[0];

	bonePointers[0] = new Bone(firstBone.boneName);
	bonePointers[0]->parentIndex = firstBone.parentIndex;
	bonePointers[0]->level = firstBone.level;

	assert(firstBone.parentIndex == -1);
	bones->insert(bonePointers[0], bones->getRoot());

	for(int boneIndex = 1; boneIndex < header.numBones; ++boneIndex) {
		const ArchiveBone& currentBone = buffBones[boneIndex];
		
		bonePointers[boneIndex] = new Bone(buffBones[boneIndex].boneName);
		bonePointers[boneIndex]->parentIndex = buffBones[boneIndex].parentIndex;
		bonePointers[boneIndex]->level = buffBones[boneIndex].level;

		assert(currentBone.parentIndex != -1);
		bones->insert(bonePointers[boneIndex], bonePointers[currentBone.parentIndex]);
		if(skeleton.getNumLevels() < currentBone.level) {
			skeleton.setNumLevels(currentBone.level);
		}
	}

	skeleton.setBones(bones);
}

void AnimationManager::loadAnimationsFromBuffer(const AnimationHeader& animationHeader, void* const buffer) {
	// Add logic to import animation data from buffer

	// Animation header has number of animations
	// For each animation, name is specified as well as number of keyframes
		// For each keyframe, keyframe time is specified as well as number of transforms
			// For each transform, store away the data as part of bone data for the given timespan

}