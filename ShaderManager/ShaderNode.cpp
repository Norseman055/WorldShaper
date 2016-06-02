#include "ShaderNode.h"

#include "Shader.h"

ShaderType ShaderNode::getType() const {
	return this->type;
}

ShaderNode::ShaderNode(Shader* const shader)
	: NodeLink(shader), type(shader->getType()) { }

ShaderNode::~ShaderNode() { }