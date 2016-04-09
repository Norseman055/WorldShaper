#pragma once

#include "CameraTypes.h"
#include "Model.h"

class Camera : public Model {
public:
	CameraType getType() const;
	const char* getName() const;

	Camera( const CameraType, const char* );
	~Camera();

private:
	CameraType type;
	const char* name;
};