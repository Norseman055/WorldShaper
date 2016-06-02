#include "CameraNode.h"

#include "Camera.h"

CameraType CameraNode::getType() const {
	return this->type;
}

const char* CameraNode::getName() const {
	return this->name;
}

CameraNode::CameraNode(Camera* const camera)
	: NodeLink(camera), type(camera->getType()), name(camera->getName()) { }

CameraNode::~CameraNode() { }