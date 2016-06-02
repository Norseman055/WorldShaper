#pragma once

#include "NodeLink.h"
#include "GameObjectTypes.h"

class GameObject;
class Camera;

class GameObjectNode : public NodeLink<GameObject*> {
public:
	GameObjectType getType() const;
	const char* getName() const;

	void updateNode(const float);
	void drawNode(Camera* const);

	GameObjectNode(GameObject* const);
	~GameObjectNode();

private:
	GameObjectType type;
	const char* name;
};