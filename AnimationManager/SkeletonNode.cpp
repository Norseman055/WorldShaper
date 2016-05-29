#include "SkeletonNode.h"

#include "Skeleton.h"

const char* SkeletonNode::getName() const {
	return this->name;
}

SkeletonNode::SkeletonNode(Skeleton* const skeleton)
	: NodeLink(skeleton), name(skeleton->getName()) { }

SkeletonNode::~SkeletonNode() { }