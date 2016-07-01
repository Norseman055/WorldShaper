#include "Skeleton.h"

#include "PlaybackControls.h"
#include "AnimationController.h"
#include "Bone.h"

#include <PCSTree\PCSTree.h>
#include <Math\MathEngine.h>
#include <assert.h>
#include <string.h>

const char* Skeleton::getName() const {
	return this->name;
}

PCSTree* Skeleton::getBones() const {
	return this->bones;
}

void Skeleton::setBones(PCSTree* const inBones) {
	this->bones = inBones;
}

void Skeleton::addAnimations(AnimationController* const animations) {
	this->animations = animations;
}

void Skeleton::setAnimationPlayback(const PlaybackControl control) {
	this->animations->setAnimationPlayback(control);
}

void Skeleton::setCurrentAnimation(const char* animName) {
	this->animations->setCurrentAnimation(animName);
}

void Skeleton::updateAnimation(const float gametime) const {
	this->animations->updateAnimation(gametime);
	this->updateBonePose(static_cast<Bone*>(this->bones->getRoot()));
}

void Skeleton::drawBones(Camera* const camera) const {
	Bone* root = static_cast<Bone*>(this->bones->getRoot());
	if(root) {
		recursiveDrawBones(root, camera);
	}
}

void Skeleton::recursiveDrawBones(Bone* const bone, Camera* const camera) const {
	bone->draw(camera);

	Bone* child;
	if(bone->getChild()) {
		child = static_cast<Bone*>(bone->getChild());
		while(child) {
			recursiveDrawBones(child, camera);
			child = static_cast<Bone*>(child->getSibling());
		}
	}
}

void Skeleton::updateBonePose(Bone* const bone) const {
	setBonePose(bone);

	Bone* child;
	if(bone->getChild()) {
		child = static_cast<Bone*>(bone->getChild());
		while(child) {
			updateBonePose(child);
			child = static_cast<Bone*>(child->getSibling());
		}
	}
}

void Skeleton::setBonePose(Bone* const bone) const {
	Bone* child = bone;
	Bone* parent = static_cast<Bone*>(bone->getParent());

	if(parent && parent != this->bones->getRoot() && child) {
		Vect start(0.0f, 0.0f, 0.0f);

		parent->transform(this->animations->getCurrentAnimation());
		Vect ptA = start * *parent->getWorld();

		child->transform(this->animations->getCurrentAnimation());
		Vect ptB = start * *child->getWorld();

		// direction between anchor points of respective bones
		const Vect dir = -(ptB - ptA);

		// length of bone
		const float mag = dir.mag();

		// set orientation and length
		Matrix S(SCALE, BONE_WIDTH, BONE_WIDTH, mag);
		Quat R(ROT_ORIENT, dir.getNorm(), Vect(0.0f, 1.0f, 0.0f));
		Matrix T(TRANS, ptB);

		Matrix boneOrient = S * R * T;

		child->setBoneOrientation(&boneOrient);
	}
}

void Skeleton::removeAnimations() {
	this->animations = nullptr;
}

AnimationController* Skeleton::getAnimations() const {
	return this->animations;
}

void Skeleton::addBindPose(Matrix* const bindPose) {
	this->bindPose = bindPose;
}

Matrix* Skeleton::getBindPose() const {
	return this->bindPose;
}

void Skeleton::addSkinInfluence(SkinArray* const skinInfluence) {
	this->skinInfluence = skinInfluence;
}

SkinArray* Skeleton::getSkinInfluence() const {
	return this->skinInfluence;
}

int Skeleton::getNumLevels() const {
	return this->numLevels;
}

void Skeleton::setNumLevels(const int numLevels) {
	this->numLevels = numLevels;
}

Skeleton::Skeleton(const char* inName)
	: bones(nullptr), animations(nullptr), bindPose(nullptr), skinInfluence(nullptr), numBones(0), numLevels(0) {
	assert(inName);
	int nameLen = strlen(inName);
	this->name = new char[nameLen + 1];
	strcpy(this->name, inName);
}

Skeleton::~Skeleton() { }