#include "CameraManager.h"
#include "Macros.h"

#include "CameraNode.h"
#include "Camera.h"

void CameraManager::Startup() {
	printf("\n===== CAMERA MANAGER : START =====\n");
	GetInstance();
	LoadCameras();
	printf("===== CAMERA MANAGER : FINISHED STARTING =====\n\n");
}

void CameraManager::Shutdown() {
	Cleanup();
	DestroyInstance();
}

void CameraManager::AddCamera(Camera* const camera) {
	Add(new CameraNode(camera));
}

void CameraManager::RemoveCamera(const CameraType type, const char* name) {
	Remove(Find(type, name));
}

Camera* CameraManager::FindCamera(const CameraType type, const char* name) {
	Camera* camera = nullptr;
	CameraNode* cameraNode = Find(type, name);
	if(cameraNode) {
		camera = cameraNode->getData();
	}
	return camera;
}

Camera* CameraManager::GetActiveCamera() {
	return static_cast<CameraManager*>(GetInstance())->activeCamera;
}

void CameraManager::UpdateActiveCamera() {
	static_cast<CameraManager*>(GetInstance())->activeCamera->updateCamera();
}

void CameraManager::FramebufferResizeCallback(GLFWwindow* window, int width, int height) {
	UNUSED(window);

	static_cast<CameraManager*>(GetInstance())->activeCamera->setViewportHeightWidth(height, width);
}

void CameraManager::LoadCameras() {
	printf("CAMERA MANAGER: Loading cameras...\n");
	Camera* cam0 = new Camera(CameraType::Camera_Default, "default");
	cam0->setPerspective(1.0f, 10000.0f, 35.0f, float(GAME_WIDTH) / float(GAME_HEIGHT));
	cam0->setViewport(0, 0, GAME_HEIGHT, GAME_WIDTH);
	cam0->setOrientationAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(250.0f, 400.0f, 400.0f));
	AddCamera(cam0);

	printf("CAMERA MANAGER: Setting default camera to \"default\"\n");
	static_cast<CameraManager*>(GetInstance())->activeCamera = FindCamera(CameraType::Camera_Default, "default");
}

CameraNode* CameraManager::Find(const CameraType type, const char* name) {
	CameraNode* camera = nullptr;
	if(type != CameraType::Camera_None) {
		CameraNode* root = static_cast<CameraNode*>(GetObjectList()->getRoot());

		if(root) {
			camera = static_cast<CameraManager*>(GetInstance())->findDepthFirst(root, type, name);
		}
	}
	return camera;
}

CameraNode* CameraManager::findDepthFirst(CameraNode* const walker, const CameraType type, const char* name) const {
	CameraNode* camera = nullptr;
	if(walker->getType() == type) {
		camera = walker;
	} else {
		if(walker->getChild()) {
			camera = this->findDepthFirst(static_cast<CameraNode*>(walker->getChild()), type, name);
		}
		if(!camera && walker->getSibling()) {
			camera = this->findDepthFirst(static_cast<CameraNode*>(walker->getSibling()), type, name);
		}
	}
	return camera;
}