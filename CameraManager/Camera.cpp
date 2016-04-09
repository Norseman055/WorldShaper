#include "Camera.h"

#include <stdio.h>

CameraType Camera::getType() const {
	return this->type;
}

Camera::Camera( CameraType inType, const char* name )
	: GameObject(GameObjectType::GameObject_Camera, name), type( inType ) { }

Camera::~Camera() { }