#include "GameObjectNode.h"

#include "GameObject.h"

GameObjectType GameObjectNode::getType() const {
	return this->type;
}

const char* GameObjectNode::getName() const {
	return this->name;
}

void GameObjectNode::updateNode( const double gameTime ) {
	this->getData()->update( gameTime );
}

void GameObjectNode::drawNode(Camera* const camera) {
	this->getData()->draw(camera);
}

GameObjectNode::GameObjectNode( GameObject* const gameObject )
	: NodeLink( gameObject ), type( gameObject->getType() ), name( gameObject->getName() ) { }

GameObjectNode::~GameObjectNode() { }