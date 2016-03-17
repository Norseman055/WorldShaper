#pragma once

#include "Manager.h"
#include "ShaderTypes.h"

class ShaderNode;
class Shader;

class ShaderManager : public Manager<Shader> {
public:
	static void Startup();
	static void Shutdown();

	static void AddShader( Shader* const );
	static void RemoveShader( const ShaderType );

	static Shader* FindShader( const ShaderType );

private:
	static void LoadShaders();
	static ShaderNode* Find( const ShaderType );

	ShaderNode* findDepthFirst( ShaderNode* const, const ShaderType );
};