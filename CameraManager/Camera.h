#pragma once

#include "CameraTypes.h"
#include "Model.h"

#include "Math\MathEngine.h"

class Camera : public Model, public Align16 {
public:
	CameraType getType() const;
	const char* getName() const;

	Matrix& getViewMatrix();
	Matrix& getProjectionMatrix();
	Vect& getPosition();

	void setPerspective( const float, const float, const float, const float );
	void setViewport( const float, const float, const float, const float );
	void setOrientationAndPosition( const Vect&, const Vect&, const Vect& );

	void updateCamera();

	Camera( const CameraType, const char* );
	~Camera();

private:
	void updateViewPlane();
	void updateFrustrumVerts();
	void updateFrustrumCollisionNormals();
	void updateViewMatrix();
	void updateProjectionMatrix();

	void setGlfwViewport()const;

private:
	// Matrices
	Matrix viewMatrix;
	Matrix projectionMatrix;

	// Unit Vectors (up, forward, right)
	Vect up;
	Vect forward;
	Vect right;
	Vect position;
	Vect lookAt;

	// Viewing frustrum worldspace coordinates
	Vect nearTopLeft;
	Vect nearTopRight;
	Vect nearBottomLeft;
	Vect nearBottomRight;
	Vect farTopLeft;
	Vect farTopRight;
	Vect farBottomLeft;
	Vect farBottomRight;

	// Viewing frustrum normals
	Vect frontNormal;
	Vect backNormal;
	Vect leftNormal;
	Vect rightNormal;
	Vect topNormal;
	Vect bottomNormal;

	// Viewing frustrum inputs
	float nearDist;
	float farDist;
	float fovy;	// Field of View Y - in degrees
	float aspectRatio;

	// Screen dimensions in worldspace
	float nearHeight;
	float nearWidth;
	float farHeight;
	float farWidth;

	// Viewport
	float viewportX;
	float viewportY;
	float viewportHeight;
	float viewportWidth;

	CameraType type;
	const char* name;

};