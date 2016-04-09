#pragma once

#include "NodeLink.h"
#include "CameraTypes.h"

class Camera;

class CameraNode : public NodeLink<Camera*> {
public:
	CameraType getType() const;
	const char* getName() const;

	CameraNode( Camera* const );
	~CameraNode();

private:
	CameraType type;
	const char* name;
};