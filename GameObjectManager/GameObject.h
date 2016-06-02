#pragma once

#include "GameObjectTypes.h"

class Model;
class Texture;
class Shader;
class Camera;
class Skeleton;

class GameObject {
public:
	GameObjectType getType() const;
	const char* getName() const;

	void setModel(Model* const);
	void setTexture(Texture* const);
	void setShader(Shader* const);
	void setSkeleton(Skeleton* const);

	void update(const double) const;
	void draw(Camera* const) const;

	GameObject(const GameObjectType, const char*);
	~GameObject();

private:
	GameObjectType type;
	const char* name;

	Model* model;
	Texture* texture;
	Shader* shader;
	Skeleton* skeleton;
};