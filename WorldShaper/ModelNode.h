#pragma once

#include "NodeLink.h"
#include "Model.h"
#include "ModelTypes.h"

class ModelNode : public NodeLink<Model> {
public:
	ModelType getType() {
		return this->type;
	}

	ModelNode( ModelType inType, Model* const model ) 
		: NodeLink(model), type(inType)
	{ }

private:
	ModelType type;
};