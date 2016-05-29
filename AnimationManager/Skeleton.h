#pragma once

class PCSTree;
class AnimationController;
class Animation;

class Skeleton {
public:
	const char* getName() const;

	PCSTree* getBones() const;
	void setBones(PCSTree* const bones);

	void addAnimation(Animation* const);
	void removeAnimation(Animation* const);
	Animation* find(const char*) const;

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