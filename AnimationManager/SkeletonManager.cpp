#include "SkeletonManager.h"

#include "ArchiveStructures.h"
#include "SkeletonNode.h"
#include "Skeleton.h"
#include "Bone.h"
#include <assert.h>
#include <string.h>
#include <Math\MathEngine.h>

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

void SkeletonManager::LoadBindPoseFromBuffer(const char* skeletonName, const BindPoseHeader& header, void* buffer) {
	Skeleton* skeleton = FindSkeleton(skeletonName);
	if(skeleton) {
		skeleton->addBindPose(loadBindPoseFromBuffer(header, buffer));
	}
}

void SkeletonManager::LoadSkinFromBuffer(const char* skeletonName, const SkinningHeader& header, void* buffer) {
	Skeleton* skeleton = FindSkeleton(skeletonName);
	if(skeleton) {
		skeleton->addSkinInfluence(loadSkinFromBuffer(header, buffer));
	}
}

SkeletonNode* SkeletonManager::findDepthFirst(SkeletonNode* const walker, const char* name) const {
	SkeletonNode* skeleton = nullptr;
	if(strcmp(name, walker->getName()) == 0) {
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
	printf("SKELETON MANAGER: Loading %i bones...\n", header.numBones);
	Skeleton* skeleton = new Skeleton(skeletonName);
	ArchiveBone* buffBones = reinterpret_cast<ArchiveBone*>(buffer);
	Bone** bonePointers = new Bone*[header.numBones];
	PCSTree* bones = new PCSTree();

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

Matrix* SkeletonManager::loadBindPoseFromBuffer(const BindPoseHeader& header, void* buffer) {
	printf("SKELETON MANAGER: Loading %i matrices...\n", header.numMatrices);
	ArchiveMatrix* buffArray = reinterpret_cast<ArchiveMatrix*>(buffer);
	Matrix* matrixArray = new Matrix[header.numMatrices];

	for(int i = 0; i < header.numMatrices; i++) {
		ArchiveMatrix& buffMatrix = buffArray[i];
		matrixArray[i].set(
			Vect(buffMatrix.elements[0][0], buffMatrix.elements[0][1], buffMatrix.elements[0][2], buffMatrix.elements[0][3]),
			Vect(buffMatrix.elements[1][0], buffMatrix.elements[1][1], buffMatrix.elements[1][2], buffMatrix.elements[1][3]),
			Vect(buffMatrix.elements[2][0], buffMatrix.elements[2][1], buffMatrix.elements[2][2], buffMatrix.elements[2][3]),
			Vect(buffMatrix.elements[3][0], buffMatrix.elements[3][1], buffMatrix.elements[3][2], buffMatrix.elements[3][3]));
	}

	return matrixArray;
}

SkinArray* SkeletonManager::loadSkinFromBuffer(const SkinningHeader& header, void* buffer) {
	printf("SKELETON MANAGER: Loading %i skin weight vectors...\n", header.numInfluenceVectors);
	SkinArray* buffArray = reinterpret_cast<SkinArray*>(buffer);
	SkinArray* skinArray = new SkinArray[header.numInfluenceVectors];

	for(int i = 0; i < header.numInfluenceVectors; i++) {
		skinArray[i] = buffArray[i];
	}

	return skinArray;
}