#include "GO_Humanoid.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "SkeletonManager.h"

#include "Skeleton.h"

void GO_Humanoid::setAnimation(const HumanoidAnim animation) {
	this->currAnim = animation;

	const char* animName;
	switch(animation) {
		case HumanoidAnim::Anim_Shot:
			animName = "shot";
			break;
		case HumanoidAnim::Anim_Punch:
			animName = "punch";
			break;
		case HumanoidAnim::Anim_Run:
			animName = "run";
			break;
		case HumanoidAnim::Anim_Take001:
			animName = "Take 001";
			break;
		default:
			// BIND POSE, do nothing
			animName = nullptr;
			break;
	}
	if(animName) {
		this->skeleton->setCurrentAnimation(animName);
	}
}

void GO_Humanoid::update(const float gametime) const {
	// Add update logic here
	if(this->currAnim != HumanoidAnim::Anim_BindPose) {
		this->skeleton->updateAnimation(gametime);
	}
}

void GO_Humanoid::setupHumanoid() {
	this->setModel(ModelManager::FindModel(ModelType::Model_Generic));
	this->setTexture(TextureManager::FindTexture(TextureType::Texture_Brick));
	this->setShader(ShaderManager::FindShader(ShaderType::Shader_Phong));
	this->setSkeleton(SkeletonManager::FindSkeleton("humanoid2"));
}

GO_Humanoid::GO_Humanoid(const char* name)
	: GameObject(GameObjectType::GameObject_Generic, name), currAnim(HumanoidAnim::Anim_BindPose) {
	printf("GO_HUMANOID: Creating Humanoid - %s...\n", name);
	this->setupHumanoid();
}

GO_Humanoid::~GO_Humanoid() { }