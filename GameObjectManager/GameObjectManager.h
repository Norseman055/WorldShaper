#pragma once

#include "Manager.h"
#include "GameObjectTypes.h"

class GameObjectNode;
class GameObject;

class GameObjectManager : public Manager<GameObject> {
public:
	static void Startup();
	static void Shutdown();

	static void AddGameObject( GameObject* const );
	static void RemoveGameObject( const GameObjectType, const char* );

	static GameObject* FindGameObject( const GameObjectType, const char* );

private:
	static void LoadGameObjects();
	static GameObjectNode* Find( const GameObjectType, const char* );

	GameObjectNode* findTypeTree( GameObjectNode* const, const GameObjectType );
	GameObjectNode* findDepthFirst( GameObjectNode* const, const char * );
};