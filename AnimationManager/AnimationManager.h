#pragma once

#include "Singleton.h"

class AnimationNode;
class Animation;
class Skeleton;
struct ModelFileHeader;
struct SkeletonHeader;
struct AnimationHeader;

class AnimationManager : Singleton<AnimationManager> {
friend class Singleton<AnimationManager>;
public:
	static void Startup();
	static void Shutdown();

	static void LoadAnimationFromBuffer(ModelFileHeader&, char* const);
};