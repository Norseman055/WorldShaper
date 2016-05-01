#pragma once

#include "Manager.h"

class AnimationNode;
class Animation;

class AnimationManager : public Manager<Animation*> {
public:
	static void Startup();
	static void Shutdown();

	static void AddAnimation(Animation* const);
	static void RemoveAnimation(const char*);

	static Animation* FindAnimation(const char*);
	
private:
	static void LoadAnimations();
	static AnimationNode* Find(const char*);

	AnimationNode* findDepthFirst(AnimationNode* const, const char *) const;
};