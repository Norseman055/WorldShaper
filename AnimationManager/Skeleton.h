#pragma once

class PCSTree;
class AnimationController;

class Skeleton {
public:
	const char* getName() const;

	PCSTree* getBones() const;
	void setBones(PCSTree* const bones);

	void addAnimations(AnimationController* const);
	void removeAnimations();
	AnimationController* getAnimations() const;

	int getNumLevels() const;
	void setNumLevels(const int);

	Skeleton(const char*);
	~Skeleton();

private:
	char* name;
	PCSTree* bones;
	AnimationController* animations;
	int numBones;
	int numLevels;
};