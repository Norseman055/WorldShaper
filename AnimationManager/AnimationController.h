#pragma once

#include <list>

class Animation;

class AnimationController {
public:
	const char* getName() const;

	void AddAnimation(Animation* const);
	void RemoveAnimation(Animation* const);

	Animation* FindAnimation(const char*) const;

	AnimationController(const char*);
	~AnimationController();

private:
	char* skeletonName;	// name of skeleton animations are associated with
	std::list<Animation*> animations;
};