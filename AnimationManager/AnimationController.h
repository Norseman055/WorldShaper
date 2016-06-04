#pragma once

#include <list>

class Animation;
enum struct PlaybackControl;

class AnimationController {
public:
	const char* getName() const;

	void addAnimation(Animation* const);
	void setAnimationPlayback(const PlaybackControl);
	void setCurrentAnimation(const char*);
	void updateAnimation(const float);
	void removeAnimation(Animation* const);

	Animation* findAnimation(const char*) const;

	AnimationController(const char*);
	~AnimationController();

private:
	void switchTime(const float);

private:
	char* skeletonName;	// name of skeleton animations are associated with
	std::list<Animation*> animations;
	Animation* currentAnimation;
	PlaybackControl playbackControl;
	float tCurrent;
};