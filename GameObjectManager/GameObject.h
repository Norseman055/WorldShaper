#pragma once

#include "GameObjectTypes.h"

class Model;
class Texture;
class Shader;
class Camera;
class Skeleton;
class Matrix;
class Animation;

class GameObject {
public:
	GameObjectType getType() const;
	const char* getName() const;

	void setModel(Model* const);
	void setTexture(Texture* const);
	void setShader(Shader* const);
	void setSkeleton(Skeleton* const);

	Matrix* getWorld() const;

	virtual void transform(Animation* const) = 0;
	virtual void update(const float) const;
	virtual void draw(Camera* const) const;

	GameObject(const GameObjectType, const char*);
	virtual ~GameObject() = 0;

protected:
	Model* model;
	Texture* texture;
	Shader* shader;
	Skeleton* skeleton;

	Matrix* local;
	Matrix* world;
	Matrix* boneOrientation;

private:
	GameObjectType type;
	const char* name;
};