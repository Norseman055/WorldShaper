#include "ModelNode.h"

#include "Model.h"

ModelType ModelNode::getType() const {
	return this->type;
}

ModelNode::ModelNode(Model* const model)
	: NodeLink(model), type(model->getType()) { }

ModelNode::~ModelNode() { }