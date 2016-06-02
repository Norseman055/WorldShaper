#pragma once

#include "ShaderTypes.h"

class Shader {
public:
	ShaderType getType() const;
	unsigned int getShaderID() const;

	void setupGLSLShaders(const char*);

	Shader(const ShaderType, const char*);
	~Shader();

private:
	ShaderType type;
	unsigned int shaderProgram;
	unsigned int vertexShader;
	unsigned int fragmentShader;
};