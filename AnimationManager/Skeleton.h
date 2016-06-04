#pragma once

class PCSTree;
class AnimationController;
class Matrix;
struct SkinArray;
enum struct PlaybackControl;

class Skeleton {
public:
	const char* getName() const;

	PCSTree* getBones() const;
	void setBones(PCSTree* const bones);

	void addAnimations(AnimationController* const);
	void removeAnimations();

	void setAnimationPlayback(const PlaybackControl);
	void setCurrentAnimation(const char*);
	void updateAnimation(const float) const;

	AnimationController* getAnimations() const;

	void addBindPose(Matrix* const);
	Matrix* getBindPose() const;

	void addSkinInfluence(SkinArray* const);
	SkinArray* getSkinInfluence() const;

	int getNumLevels() const;
	void setNumLevels(const int);

	Skeleton(const char*);
	~Skeleton();

private:
	char* name;
	PCSTree* bones;
	AnimationController* animations;
	Matrix* bindPose;
	SkinArray* skinInfluence;
	int numBones;
	int numLevels;
};