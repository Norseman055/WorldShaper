#pragma once

#include "Manager.h"
#include "GameObjectTypes.h"

class GameObjectNode;
class GameObject;

/** 
 * GAME OBJECT MANAGER
 *   This manager handles adding, removing, updating and drawing game objects stored in a PCSTree organized as a scene graph.
 *   The update function will update the objects in the scene graph, with the parent objects being updated first.
 *   The draw function will draw the objects in the scene graph, with the parent objects being drawn first
 */
class GameObjectManager : public Manager<GameObject*> {
public:
	static void Startup();
	static void Shutdown();

	static void Update( const double );
	static void Draw();

	static void AddGameObject( GameObject* const );
	static void RemoveGameObject( const GameObjectType, const char* );

	static GameObject* FindGameObject( const GameObjectType, const char* );

private:
	static void LoadGameObjects();
	static GameObjectNode* Find( const GameObjectType, const char* );

	GameObjectNode* findDepthFirst( GameObjectNode* const, const GameObjectType, const char * ) const;
	
	void updatePtC( const double, GameObjectNode* const ) const;
	void drawPtC( GameObjectNode* const ) const;
};