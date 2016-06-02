#pragma once

#include "NodeLink.h"
#include "ShaderTypes.h"

class Shader;

class ShaderNode : public NodeLink<Shader*> {
public:
	ShaderType getType() const;

	ShaderNode(Shader* const);
	~ShaderNode();

private:
	ShaderType type;
};