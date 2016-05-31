#include "SkeletonManager.h"

#include "ArchiveStructures.h"
#include "SkeletonNode.h"
#include "Skeleton.h"
#include "Bone.h"
#include <assert.h>
#include <string.h>

void SkeletonManager::AddSkeleton(Skeleton* const skeleton) {
	Add(new SkeletonNode(skeleton));
}

void SkeletonManager::RemoveSkeleton(const char* name) {
	Remove(Find(name));
}

void SkeletonManager::AssignAnimationsToSkeleton(const char* skeletonName, AnimationController* const animationController) {
	Skeleton* skeleton = FindSkeleton(skeletonName);
	if(skeleton) {
		skeleton->addAnimations(animationController);
	}
}

Skeleton* SkeletonManager::FindSkeleton(const char* name) {
	Skeleton* skeleton = nullptr;
	SkeletonNode* skeletonNode = Find(name);
	if(skeletonNode) {
		skeleton = skeletonNode->getData();
	}
	return skeleton;
}

SkeletonNode* SkeletonManager::Find(const char* name) {
	SkeletonNode* skeleton = nullptr;
	if(name) {
		SkeletonNode* root = static_cast<SkeletonNode*>(GetObjectList()->getRoot());

		if(root) {
			skeleton = static_cast<SkeletonManager*>(GetInstance())->findDepthFirst(root, name);
		}
	}
	return skeleton;
}


void SkeletonManager::LoadSkeletonFromBuffer(const char* skeletonName, const SkeletonHeader& header, void* buffer) {
	AddSkeleton(loadSkeletonFromBuffer(skeletonName, header, buffer));
}

SkeletonNode* SkeletonManager::findDepthFirst(SkeletonNode* const walker, const char* name) const {
	SkeletonNode* skeleton = nullptr;
	if(strcmp(name, walker->getName())) {
		skeleton = walker;
	} else {
		if(walker->getChild()) {
			skeleton = this->findDepthFirst(static_cast<SkeletonNode*>(walker->getChild()), name);
		}
		if(!skeleton && walker->getSibling()) {
			skeleton = this->findDepthFirst(static_cast<SkeletonNode*>(walker->getSibling()), name);
		}
	}
	return skeleton;
}

Skeleton* SkeletonManager::loadSkeletonFromBuffer(const char* skeletonName, const SkeletonHeader& header, void* buffer) {
	printf("      Loading %i bones...\n ", header.numBones);
	Skeleton* skeleton = new Skeleton(skeletonName);
	ArchiveBone* buffBones = reinterpret_cast<ArchiveBone*>(buffer);
	Bone** bonePointers = new Bone*[header.numBones];
	PCSTree* bones = skeleton->getBones();

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
		if(skeleton->getNumLevels() < currentBone.level) {
			skeleton->setNumLevels(currentBone.level);
		}
	}
	skeleton->setBones(bones);

	return skeleton;
}