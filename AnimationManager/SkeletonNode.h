#pragma once

#include "NodeLink.h"

class Skeleton;

class SkeletonNode : public NodeLink<Skeleton*> {
public:
	const char* getName() const;

	SkeletonNode(Skeleton* const);
	~SkeletonNode();

private:
	const char* name;
};