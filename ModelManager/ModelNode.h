#pragma once

#include "NodeLink.h"
#include "ModelTypes.h"

class Model;

class ModelNode : public NodeLink<Model> {
public:
	ModelType getType() const;

	ModelNode( Model* const model );
	~ModelNode();

private:
	ModelType type;
};