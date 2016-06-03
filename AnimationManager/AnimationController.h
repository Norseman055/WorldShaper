#pragma once

#include <list>

class Animation;

class AnimationController {
public:
	enum struct PlaybackControl {
		PLAY,
		PLAY_LOOP,
		REWIND,
		REWIND_LOOP,
		PAUSE
	};

	const char* getName() const;

	void addAnimation(Animation* const);
	void setCurrentAnimation(const char*);
	void updateAnimation(const float);
	void removeAnimation(Animation* const);

	Animation* findAnimation(const char*) const;

	AnimationController(const char*);
	~AnimationController();

private:
	float switchTime(const float);

private:
	char* skeletonName;	// name of skeleton animations are associated with
	std::list<Animation*> animations;
	Animation* currentAnimation;
	PlaybackControl playbackControl;
	float tCurrent;
};