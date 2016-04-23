#pragma once

#include "Manager.h"
#include "CameraTypes.h"

class CameraNode;
class Camera;
struct GLFWwindow;

class CameraManager : public Manager<Camera*> {
public:
	static void Startup();
	static void Shutdown();

	static void AddCamera(Camera* const);
	static void RemoveCamera(const CameraType, const char*);

	static Camera* FindCamera(const CameraType, const char*);
	static Camera* GetActiveCamera();

	static void UpdateActiveCamera();

	static void FramebufferResizeCallback(GLFWwindow*, int, int);

private:
	static void LoadCameras();
	static CameraNode* Find(const CameraType, const char*);

	CameraNode* findDepthFirst(CameraNode* const, const CameraType, const char*) const;

private:
	Camera* activeCamera;
};