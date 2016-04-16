#include "Camera.h"

#include <stdio.h>
#include <math.h>

#define GLEW_STATIC
#include <glew\glew.h>
#include <GLFW\glfw3.h>

CameraType Camera::getType() const {
	return this->type;
}

const char* Camera::getName() const {
	return this->name;
}

Matrix& Camera::getViewMatrix() {
	return this->viewMatrix;
}

Matrix& Camera::getProjectionMatrix() {
	return this->projectionMatrix;
}

Vect& Camera::getPosition() {
	return this->position;
}

void Camera::setPerspective( const float inNear, const float inFar, const float inFovy, const float inAspect ) {
	this->nearDist = inNear;
	this->farDist = inFar;
	this->fovy = inFovy;
	this->aspectRatio = inAspect;
}

void Camera::setViewport( const float x, const float y, const float height, const float width ) {
	this->viewportX = x;
	this->viewportY = y;
	this->viewportHeight = height;
	this->viewportWidth = width;

	this->setGlfwViewport();
}

void Camera::setOrientationAndPosition( const Vect& inUp, const Vect& inLookAt, const Vect& inPos ) {
	this->lookAt = inLookAt;

	// Point out of the screen into your EYE
	this->forward = inPos - inLookAt;
	this->forward.norm();

	// Clean up the vectors (Right hand rule)
	this->right = inUp.cross( this->forward );
	this->right.norm();

	this->up = this->forward.cross( this->right );
	this->up.norm();

	this->position = inPos;
}

void Camera::updateCamera() {
	// Find near and far height/width
	this->updateViewPlane();

	// Find frustrum verts
	this->updateFrustrumVerts();

	// Find frustrum collision normals
	this->updateFrustrumCollisionNormals();

	// Update view matrix
	this->updateViewMatrix();

	// Update projection matrix
	this->updateProjectionMatrix();
}

void Camera::updateViewPlane() {
	this->nearHeight = 2.0f * tanf( (this->fovy * MATH_PI / 180.0f) * .5f ) * this->nearDist;
	this->nearWidth = this->nearHeight * this->aspectRatio;

	this->farHeight = 2.0f * tanf( (this->fovy * MATH_PI / 180.0f) * .5f ) * this->farDist;
	this->farWidth = this->farHeight * this->aspectRatio;
}

void Camera::updateFrustrumVerts() {
	this->nearTopLeft = this->position - this->forward * this->nearDist + this->up * this->nearHeight * 0.5f - this->right * this->nearWidth * 0.5f;
	this->nearTopRight = this->position - this->forward * this->nearDist + this->up * this->nearHeight * 0.5f + this->right * this->nearWidth * 0.5f;
	this->nearBottomLeft = this->position - this->forward * this->nearDist - this->up * this->nearHeight * 0.5f - this->right * this->nearWidth * 0.5f;
	this->nearBottomRight = this->position - this->forward * this->nearDist - this->up * this->nearHeight * 0.5f + this->right * this->nearWidth * 0.5f;
	this->farTopLeft = this->position - this->forward * this->farDist + this->up * this->farHeight * 0.5f - this->right * this->farWidth * 0.5f;
	this->farTopRight = this->position - this->forward * this->farDist + this->up * this->farHeight * 0.5f + this->right * this->farWidth * 0.5f;
	this->farBottomLeft = this->position - this->forward * this->farDist - this->up * this->farHeight * 0.5f - this->right * this->farWidth * 0.5f;
	this->farBottomRight = this->position - this->forward * this->farDist - this->up * this->farHeight * 0.5f + this->right * this->farWidth * 0.5f;
}

void Camera::updateFrustrumCollisionNormals() {
	// Normals of the frustum around nearTopLeft
	Vect A = this->nearBottomLeft - this->nearTopLeft;
	Vect B = this->nearTopRight - this->nearTopLeft;
	Vect C = this->farTopLeft - this->nearTopLeft;

	this->frontNormal = A.cross( B );
	this->frontNormal.norm();

	this->leftNormal = C.cross( A );
	this->leftNormal.norm();

	this->topNormal = B.cross( C );
	this->topNormal.norm();

	// Normals of the frustum around farBottomRight
	A = this->farBottomLeft - this->farBottomRight;
	B = this->farTopRight - this->farBottomRight;
	C = this->nearBottomRight - this->farBottomRight;

	this->backNormal = A.cross( B );
	this->backNormal.norm();

	this->rightNormal = B.cross( C );
	this->rightNormal.norm();

	this->bottomNormal = C.cross( A );
	this->bottomNormal.norm();
}

void Camera::updateViewMatrix() {
	// This functions assumes the your up, right, and forward vectors are still unit
	// And perpendicular to each other
	// view = Rot(orient) * trans(-(eye.basis) )

	this->viewMatrix[m0] = this->right[x];
	this->viewMatrix[m1] = this->up[x];
	this->viewMatrix[m2] = this->forward[x];
	this->viewMatrix[m3] = 0.0f;

	this->viewMatrix[m4] = this->right[y];
	this->viewMatrix[m5] = this->up[y];
	this->viewMatrix[m6] = this->forward[y];
	this->viewMatrix[m7] = 0.0f;

	this->viewMatrix[m8] = this->right[z];
	this->viewMatrix[m9] = this->up[z];
	this->viewMatrix[m10] = this->forward[z];
	this->viewMatrix[m11] = 0.0f;

	// Change of basis (dot with the basis vectors)
	this->viewMatrix[m12] = -position.dot( right );
	this->viewMatrix[m13] = -position.dot( up );
	this->viewMatrix[m14] = -position.dot( forward );
	this->viewMatrix[m15] = 1.0f;
}

void Camera::updateProjectionMatrix() {
	this->projectionMatrix[m0] = 2.0f * this->nearDist / this->nearWidth;
	this->projectionMatrix[m1] = 0.0f;
	this->projectionMatrix[m2] = 0.0f;
	this->projectionMatrix[m3] = 0.0f;

	this->projectionMatrix[m4] = 0.0f;
	this->projectionMatrix[m5] = 2.0f * this->nearDist / this->nearHeight;
	this->projectionMatrix[m6] = 0.0f;
	this->projectionMatrix[m7] = 0.0f;

	this->projectionMatrix[m8] = 0.0f;
	this->projectionMatrix[m9] = 0.0f;
	this->projectionMatrix[m10] = (this->farDist + this->nearDist) / (this->nearDist - this->farDist);
	this->projectionMatrix[m11] = -1.0f;

	this->projectionMatrix[m12] = 0.0f;
	this->projectionMatrix[m13] = 0.0f;
	this->projectionMatrix[m14] = (2.0f * this->farDist * this->nearDist) / (this->nearDist - this->farDist);
	this->projectionMatrix[m15] = 0.0f;
}

void Camera::setGlfwViewport() const {
	glViewport(this->viewportX, this->viewportY, this->viewportWidth, this->viewportHeight);
}

Camera::Camera( CameraType inType, const char* inName )
	: Model( ModelType::Model_None ), type( inType ), name( inName ),
	nearDist( 0 ), farDist( 0 ), fovy( 0 ), aspectRatio( 0 ),
	nearHeight( 0 ), nearWidth( 0 ), farHeight( 0 ), farWidth( 0 ),
	viewportX( 0 ), viewportY( 0 ), viewportHeight( 0 ), viewportWidth( 0 ) {
	this->viewMatrix.set( IDENTITY );
	this->projectionMatrix.set( IDENTITY );
	printf( "    Creating camera...\n" );
}

Camera::~Camera() { }