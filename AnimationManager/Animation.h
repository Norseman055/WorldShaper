#pragma once

class Keyframe;

class Animation {
public:
	const char* getName() const;
	void setName(const char*);

	int getNumKeyframes() const;
	void setNumKeyframes(const int);

	Keyframe* const getKeyframes() const;
	void setKeyframes(Keyframe* const);

	Keyframe* const getResult() const;

	float getMaxTime() const;
	void getBoundingKeyframes(const float, Keyframe*, Keyframe*) const;

	void update(const float);

	Animation();
	~Animation();

private:
	char* name;
	int numKeyframes;
	Keyframe* keyframes;
	Keyframe* result;
};