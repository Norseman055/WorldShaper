#pragma once

#include "Manager.h"

class AnimationControllerNode;
class AnimationController;
struct AnimationHeader;

class AnimationControllerManager : public Manager<AnimationController*> {
public:
	static void AddAnimationController(AnimationController* const);
	static void RemoveAnimationController(const char*);

	static AnimationController* FindAnimationController(const char*);

	static void LoadAnimationsFromBuffer(const char*, const AnimationHeader&, void*);

private:
	static AnimationControllerNode* Find(const char*);

	AnimationControllerNode* findDepthFirst(AnimationControllerNode* const, const char*) const;

	static AnimationController* loadAnimationsFromBuffer(const char*, const AnimationHeader&, void*);
};