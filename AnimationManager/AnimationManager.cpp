#include "AnimationManager.h"
#include "Macros.h"

#include "ArchiveStructures.h"
#include "AnimationControllerManager.h"
#include "SkeletonManager.h"

void AnimationManager::Startup() {
	printf("\n===== Starting Animation Manager =====\n");
	GetInstance();
	printf("===== Animation Manager started =====\n\n");
}

void AnimationManager::Shutdown() {
	DestroyInstance();
}

void AnimationManager::LoadAnimationFromBuffer(ModelFileHeader& fileHeader, char* const buffer) {
	printf("  Loading animation data from buffer... \n");
	char* ptr = buffer;

	// Go to skeleton header
	VerticesHeader* verticesHeader = reinterpret_cast<VerticesHeader*>(ptr);
	ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(verticesHeader) + verticesHeader->dataSize);
	NormalHeader* normalHeader = reinterpret_cast<NormalHeader*>(ptr);
	ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(normalHeader) + normalHeader->dataSize);
	TriangleHeader* triangleHeader = reinterpret_cast<TriangleHeader*>(ptr);
	ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(triangleHeader) + triangleHeader->dataSize);

	// Load skeleton hierarchy
	printf("    Loading skeleton hierarchy from buffer...\n");
	SkeletonHeader* skeletonHeader = reinterpret_cast<SkeletonHeader*>(ptr);
	ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(skeletonHeader));
	SkeletonManager::LoadSkeletonFromBuffer(fileHeader.modelName, *skeletonHeader, ptr);

	// Load bind pose
	printf("    Loading bind pose from buffer...\n");
	ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +skeletonHeader->dataSize);
	BindPoseHeader* bindPoseHeader = reinterpret_cast<BindPoseHeader*>(ptr);
	ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(bindPoseHeader));
	SkeletonManager::LoadBindPoseFromBuffer(fileHeader.modelName, *bindPoseHeader, ptr);

	// Load animations
	printf("    Loading animations from buffer...\n");
	ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +bindPoseHeader->dataSize);
	AnimationHeader* animationHeader = reinterpret_cast<AnimationHeader*>(ptr);
	ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(animationHeader));
	AnimationControllerManager::LoadAnimationsFromBuffer(fileHeader.modelName, *animationHeader, ptr);

	// Load skin
	printf("    Loading skin from buffer...\n");
	ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +animationHeader->dataSize);
	SkinningHeader* skinningHeader = reinterpret_cast<SkinningHeader*>(ptr);
	ptr = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(skinningHeader));
	SkeletonManager::LoadSkinFromBuffer(fileHeader.modelName, *skinningHeader, ptr);

	// Assign animations controller to skeleton
	SkeletonManager::AssignAnimationsToSkeleton(fileHeader.modelName, AnimationControllerManager::FindAnimationController(fileHeader.modelName));
}