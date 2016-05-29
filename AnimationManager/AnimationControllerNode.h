#pragma once

#include "NodeLink.h"

class AnimationController;

class AnimationControllerNode : public NodeLink<AnimationController*> {
public:
	const char* getName() const;

	AnimationControllerNode(AnimationController* const);
	~AnimationControllerNode();

private:
	const char* name;
};