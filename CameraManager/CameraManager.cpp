#include "CameraManager.h"
#include "Macros.h"

#include "CameraNode.h"
#include "Camera.h"

void CameraManager::Startup() {
	printf( "\n===== Starting Camera Manager =====\n" );
	GetInstance();
	LoadCameras();
	printf( "===== Camera Manager started =====\n\n" );
}

void CameraManager::Shutdown() {
	Cleanup();
	DestroyInstance();
}

void CameraManager::AddCamera( Camera* const camera ) {
	Add( new CameraNode( camera ) );
}

void CameraManager::RemoveCamera( const CameraType type, const char* name ) {
	Remove( Find( type, name ) );
}

Camera* CameraManager::FindCamera( const CameraType type, const char* name ) {
	Camera* camera = nullptr;
	CameraNode* cameraNode = Find( type, name );
	if ( cameraNode ) {
		camera = cameraNode->getData();
	}
	return camera;
}

void CameraManager::Update( const double gameTime ) {
	// Add update logic for cameras in manager
	UNUSED( gameTime );
}

void CameraManager::Draw() {
	// Add draw logic for cameras in manager
}

void CameraManager::LoadCameras() {
	printf( "  Loading cameras...\n" );
	AddCamera( new Camera( CameraType::Camera_Default, "default" ) );
}

CameraNode* CameraManager::Find( const CameraType type, const char* name ) {
	CameraNode* camera = nullptr;
	if ( type != CameraType::Camera_None ) {
		CameraNode* root = static_cast< CameraNode* >(GetObjectList()->getRoot());

		if ( root ) {
			camera = static_cast< CameraManager* >(GetInstance())->findDepthFirst( root, type, name );
		}
	}
	return camera;
}

CameraNode* CameraManager::findDepthFirst( CameraNode* const walker, const CameraType type, const char* name ) const {
	CameraNode* camera = nullptr;
	if ( walker->getType() == type ) {
		camera = walker;
	} else {
		if ( walker->getChild() ) {
			camera = this->findDepthFirst( static_cast< CameraNode* >(walker->getChild()), type, name );
		}
		if ( !camera && walker->getSibling() ) {
			camera = this->findDepthFirst( static_cast< CameraNode* >(walker->getSibling()), type, name );
		}
	}
	return camera;
}