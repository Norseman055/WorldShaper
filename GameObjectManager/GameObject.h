#pragma once

#include "GameObjectTypes.h"

class Model;
class Texture;

class GameObject {
public:
	GameObjectType getType() const;
	const char* getName() const;

	void setModel( Model* const );
	void setTexture( Texture* const );

	GameObject( const GameObjectType, const char* );
	~GameObject();

private:
	GameObjectType type;
	const char* name;

	Model* model;
	Texture* texture;
};