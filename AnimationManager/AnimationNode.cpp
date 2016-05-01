#include "AnimationNode.h"

#include "Animation.h"

const char* AnimationNode::getName() const {
	return this->name;
}

AnimationNode::AnimationNode(Animation* const animation)
	: NodeLink(animation), name(animation->getName()) { }

AnimationNode::~AnimationNode() { }