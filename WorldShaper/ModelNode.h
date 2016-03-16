#pragma once

#include "NodeLink.h"
#include "Model.h"
#include "ModelTypes.h"

class ModelNode : public NodeLink<Model> {
public:
	ModelType getType() {
		return this->type;
	}

	ModelNode( Model* const model ) 
		: NodeLink(model), type(model->getType())
	{ }

private:
	ModelType type;
};