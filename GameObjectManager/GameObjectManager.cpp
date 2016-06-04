#include "GameObjectManager.h"
#include "Macros.h"

#include "GameObjectNode.h"
#include "GameObject.h"
#include "GO_Cube.h"
#include "GO_Humanoid.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "SkeletonManager.h"

#include <string.h>

void GameObjectManager::Startup() {
	printf("\n===== GAME OBJECT MANAGER : START =====\n");
	GetInstance();
	LoadGameObjects();
	printf("===== GAME OBJECT MANAGER : FINISHED STARTING =====\n\n");
}

void GameObjectManager::Shutdown() {
	Cleanup();
	DestroyInstance();
}

void GameObjectManager::Update(const float gameTime) {
	// Update game objects
	GameObjectNode* root = static_cast<GameObjectNode*>(GetObjectList()->getRoot());
	if(root) {
		static_cast<GameObjectManager*>(GetInstance())->updatePtC(gameTime, root);
	}
}

void GameObjectManager::Draw(Camera* const camera) {
	// Draw game objects
	GameObjectNode* root = static_cast<GameObjectNode*>(GetObjectList()->getRoot());
	if(root) {
		static_cast<GameObjectManager*>(GetInstance())->drawPtC(root, camera);
	}
}

void GameObjectManager::AddGameObject(GameObject* const gameObject) {
	Add(new GameObjectNode(gameObject));
}

void GameObjectManager::RemoveGameObject(const GameObjectType type, const char* name) {
	Remove(Find(type, name));
}

GameObject* GameObjectManager::FindGameObject(const GameObjectType type, const char* name) {
	GameObject* gameObject = nullptr;
	GameObjectNode* gameObjectNode = Find(type, name);
	if(gameObjectNode) {
		gameObject = gameObjectNode->getData();
	}
	return gameObject;
}

void GameObjectManager::LoadGameObjects() {
	printf("GAME OBJECT MANAGER: Loading game objects...\n");
	AddGameObject(new GO_Humanoid("humanoid2"));
}

GameObjectNode* GameObjectManager::Find(const GameObjectType type, const char* name) {
	GameObjectNode* gameObject = nullptr;
	if(type != GameObjectType::GameObject_None) {
		GameObjectNode* root = static_cast<GameObjectNode*>(GetObjectList()->getRoot());
		if(root) {
			gameObject = static_cast<GameObjectManager*>(GetInstance())->findDepthFirst(root, type, name);
		}
	}
	return gameObject;
}

GameObjectNode* GameObjectManager::findDepthFirst(GameObjectNode* const walker, const GameObjectType type, const char* name) const {
	GameObjectNode* gameObject = nullptr;

	// Look for object of appropriate type and name
	if(walker->getType() == type) {
		if(strcmp(walker->getName(), name) == 0) {
			gameObject = walker;
		}
	}

	// If not what we're looking for, check children and then siblings
	if(!gameObject) {
		if(walker->getChild()) {
			gameObject = this->findDepthFirst(static_cast<GameObjectNode*>(walker->getChild()), type, name);
		}
		if(!gameObject && walker->getSibling()) {
			gameObject = this->findDepthFirst(static_cast<GameObjectNode*>(walker->getSibling()), type, name);
		}
	}

	return gameObject;
}

/*
 * Update Parent-to-Child
 * Updates the parent node, then updates the siblings, then updates the children. Will update the "oldest" sibling's children first.
 */
void GameObjectManager::updatePtC(const float gameTime, GameObjectNode* const walker) const {
	// Update node
	walker->updateNode(gameTime);

	// Update siblings, then children
	if(walker->getSibling()) {
		this->updatePtC(gameTime, static_cast<GameObjectNode*>(walker->getSibling()));
	}
	if(walker->getChild()) {
		this->updatePtC(gameTime, static_cast<GameObjectNode*>(walker->getChild()));
	}
}

/*
 * Draw Parent-to-Child
 * Draws the parent node, then draws the siblings, then draws the children. Will draw the "oldest" sibling's children first
 */
void GameObjectManager::drawPtC(GameObjectNode* const walker, Camera* const camera) const {
	// Draw node
	walker->drawNode(camera);

	// Draw siblings, then children
	if(walker->getSibling()) {
		this->drawPtC(static_cast<GameObjectNode*>(walker->getSibling()), camera);
	}
	if(walker->getChild()) {
		this->drawPtC(static_cast<GameObjectNode*>(walker->getChild()), camera);
	}
}