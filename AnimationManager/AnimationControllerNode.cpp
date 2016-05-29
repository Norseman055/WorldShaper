#include "AnimationControllerNode.h"

#include "AnimationController.h"

const char* AnimationControllerNode::getName() const {
	return this->name;
}

AnimationControllerNode::AnimationControllerNode(AnimationController* const animationController)
	: NodeLink(animationController), name(animationController->getName()) { }

AnimationControllerNode::~AnimationControllerNode() { }