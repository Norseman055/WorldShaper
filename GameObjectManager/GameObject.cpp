#include "GameObject.h"

#include <stdio.h>

GameObjectType GameObject::getType() const {
	return this->type;
}

const char* GameObject::getName() const {
	return this->name;
}

void GameObject::setModel( Model* const inModel ) {
	printf( "      Setting model...\n" );
	this->model = inModel;
}

void GameObject::setTexture( Texture* const inTexture ) {
	printf( "      Setting texture...\n" );
	this->texture = inTexture;
}

GameObject::GameObject( const GameObjectType inType, const char* inName )
	: type( inType ), name( inName ), model( nullptr ), texture( nullptr ) {
	printf( "    Creating game object...\n" );
}

GameObject::~GameObject() { }