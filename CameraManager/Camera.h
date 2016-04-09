#pragma once

#include "CameraTypes.h"
#include "GameObject.h"

class Camera : public GameObject {
public:
	CameraType getType() const;

	Camera( const CameraType, const char* );
	~Camera();

private:
	CameraType type;
};