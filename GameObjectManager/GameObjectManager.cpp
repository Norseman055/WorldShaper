#include "GameObjectManager.h"

#include "GameObjectNode.h"
#include "GameObject.h"

#include "ModelManager.h"
#include "TextureManager.h"

#include <string.h>

void GameObjectManager::Startup() {
	printf( "\n===== Starting Game Object Manager =====\n" );
	GetInstance();
	LoadGameObjects();
	printf( "===== Game Object Manager started =====\n\n" );
}

void GameObjectManager::Shutdown() {
	Cleanup();
	DestroyInstance();
}

void GameObjectManager::AddGameObject( GameObject* const gameObject ) {
	Add( new GameObjectNode( gameObject ) );
}

void GameObjectManager::RemoveGameObject( const GameObjectType type, const char* name ) {
	Remove( Find( type, name ) );
}

GameObject* GameObjectManager::FindGameObject( const GameObjectType type, const char* name ) {
	GameObject* gameObject = nullptr;
	GameObjectNode* gameObjectNode = Find( type, name );
	if ( gameObjectNode ) {
		gameObject = gameObjectNode->getData();
	}
	return gameObject;
}

void GameObjectManager::LoadGameObjects() {
	printf( "  Loading game objects...\n" );
	GameObject* cubeBrick = new GameObject( GameObject_CubeBrick, "testCube" );
	cubeBrick->setModel( ModelManager::FindModel( Model_Cube ) );
	cubeBrick->setTexture( TextureManager::FindTexture( Texture_Brick ) );
	AddGameObject( cubeBrick );
}

GameObjectNode* GameObjectManager::Find( const GameObjectType type, const char* name ) {
	GameObjectNode* gameObject = nullptr;
	if ( type != GameObject_None ) {
		GameObjectNode* root = static_cast< GameObjectNode* >(GetObjectList()->getRoot());
		GameObjectNode* typeTree = nullptr;

		if ( root ) {
			GameObjectManager* instance = static_cast< GameObjectManager* >(GetInstance());
			typeTree = instance->findTypeTree( root, type );
			if ( typeTree ) {
				gameObject = instance->findDepthFirst( gameObject, name );
			}
		}
	}
	return gameObject;
}

GameObjectNode* GameObjectManager::findTypeTree( GameObjectNode* const walker, const GameObjectType type ) {
	GameObjectNode* gameObject = nullptr;

	if ( walker->getType() == type ) {
		gameObject = walker;
	} else {
		if ( walker->getSibling() ) {
			gameObject = this->findTypeTree( static_cast< GameObjectNode* >(walker->getSibling()), type );
		}
	}
	return gameObject;
}

GameObjectNode* GameObjectManager::findDepthFirst( GameObjectNode* const walker, const char* name ) {
	GameObjectNode* gameObject = nullptr;

	if ( strcmp( walker->getName(), name ) == 0 ) {
		gameObject = walker;
	} else {
		if ( walker->getChild() ) {
			gameObject = this->findDepthFirst( static_cast< GameObjectNode* >(walker->getChild()), name );
		}
		if ( !gameObject && walker->getSibling() ) {
			gameObject = this->findDepthFirst( static_cast< GameObjectNode* >(walker->getSibling()), name );
		}
	}
	return gameObject;
}