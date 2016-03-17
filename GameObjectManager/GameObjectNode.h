#pragma once

#include "NodeLink.h"
#include "GameObjectTypes.h"

class GameObject;

class GameObjectNode : public NodeLink<GameObject> {
public:
	GameObjectType getType() const;
	const char* getName() const;

	GameObjectNode( GameObject* const );
	~GameObjectNode();

private:
	GameObjectType type;
	const char* name;
};