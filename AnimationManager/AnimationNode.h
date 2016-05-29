#pragma once

#include "NodeLink.h"

class Animation;

class AnimationNode : public NodeLink<Animation*> {
public:
	const char* getName() const;
	AnimationNode(Animation* const);
	~AnimationNode();

private:
	const char* name;
};