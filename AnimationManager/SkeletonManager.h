#pragma once

#include "Manager.h"

class SkeletonNode;
class Skeleton;
class AnimationController;
struct SkeletonHeader;

class SkeletonManager : public Manager<Skeleton*> {
public:
	static void AddSkeleton(Skeleton* const);
	static void RemoveSkeleton(const char*);
	static void AssignAnimationsToSkeleton(const char*, AnimationController* const);

	static Skeleton* FindSkeleton(const char*);

	static void LoadSkeletonFromBuffer(const char*, const SkeletonHeader&, void*);
private:
	static SkeletonNode* Find(const char*);

	SkeletonNode* findDepthFirst(SkeletonNode* const, const char*) const;

	static Skeleton* loadSkeletonFromBuffer(const char*, const SkeletonHeader&, void*);
};