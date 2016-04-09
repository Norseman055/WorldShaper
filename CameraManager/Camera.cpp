#include "Camera.h"

#include <stdio.h>

CameraType Camera::getType() const {
	return this->type;
}

const char* Camera::getName() const {
	return this->name;
}

Camera::Camera( CameraType inType, const char* inName )
	: Model( ModelType::Model_None ), type( inType ), name( inName ) { 
	printf( "    Creating camera...\n" );
}

Camera::~Camera() { }