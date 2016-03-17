#include "GameObjectNode.h"

#include "GameObject.h"

GameObjectType GameObjectNode::getType() const {
	return this->type;
}

const char* GameObjectNode::getName() const {
	return this->name;
}

GameObjectNode::GameObjectNode( GameObject* const gameObject )
	: NodeLink( gameObject ), type( gameObject->getType() ), name( gameObject->getName() ) { }

GameObjectNode::~GameObjectNode() { }