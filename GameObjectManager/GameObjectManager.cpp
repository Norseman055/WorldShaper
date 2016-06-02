#include "GameObjectManager.h"
#include "Macros.h"

#include "GameObjectNode.h"
#include "GameObject.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "SkeletonManager.h"

#include <string.h>

void GameObjectManager::Startup() {
	printf("\n===== Starting Game Object Manager =====\n");
	GetInstance();
	LoadGameObjects();
	printf("===== Game Object Manager started =====\n\n");
}

void GameObjectManager::Shutdown() {
	Cleanup();
	DestroyInstance();
}

void GameObjectManager::Update(const double gameTime) {
	// Update game objects
	GameObjectNode* root = static_cast<GameObjectNode*>(GetObjectList()->getRoot());
	if(root) {
		UNUSED(gameTime);
		// UNCOMMENT THIS WHEN UPDATE LOGIC IS IN!
		//static_cast< GameObjectManager* >(GetInstance())->updatePtC( gameTime, root );
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
	printf("  Loading game objects...\n");
	GameObject* cubeBrick = new GameObject(GameObjectType::GameObject_CubeBrick, "testCube");
	cubeBrick->setModel(ModelManager::FindModel(ModelType::Model_Cube));
	cubeBrick->setTexture(TextureManager::FindTexture(TextureType::Texture_Brick));
	cubeBrick->setShader(ShaderManager::FindShader(ShaderType::Shader_Phong));
	AddGameObject(cubeBrick);

	GameObject* humanoid2 = new GameObject(GameObjectType::GameObject_Generic, "humanoid2");
	humanoid2->setModel(ModelManager::FindModel(ModelType::Model_Generic));
	humanoid2->setTexture(TextureManager::FindTexture(TextureType::Texture_Brick));
	humanoid2->setShader(ShaderManager::FindShader(ShaderType::Shader_Phong));
	humanoid2->setSkeleton(SkeletonManager::FindSkeleton("humanoid2"));
	AddGameObject(humanoid2);
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

void GameObjectManager::updatePtC(const double gameTime, GameObjectNode* const walker) const {
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