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

	Animation();
	~Animation();

private:
	char* name;
	int numKeyframes;
	Keyframe* keyframes;
};