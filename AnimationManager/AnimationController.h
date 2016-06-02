#pragma once

#include <list>

class Animation;

class AnimationController {
public:
	enum struct PlaybackControl {
		PLAY,
		PAUSE,
		REWIND,
		LOOP
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
	void playAnimation(const float);
	void rewindAnimation(const float);
	void loopAnimation(const float);

private:
	char* skeletonName;	// name of skeleton animations are associated with
	std::list<Animation*> animations;
	Animation* currentAnimation;
	PlaybackControl playbackControl;
	float lastUpdateTime;
};