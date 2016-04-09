#include "ShaderManager.h"

#include "ShaderNode.h"
#include "Shader.h"

void ShaderManager::Startup() {
	printf( "\n===== Starting Shader Manager =====\n" );
	GetInstance();
	LoadShaders();
	printf( "===== Shader Manager started =====\n\n" );
}

void ShaderManager::Shutdown() {
	Cleanup();
	DestroyInstance();
}

void ShaderManager::AddShader( Shader* const shader ) {
	// Only add shader to manager if unique shader. No need for duplicates.
	if ( !Find( shader->getType() ) ) {
		Add( new ShaderNode( shader ) );
	}
}

void ShaderManager::RemoveShader( const ShaderType type ) {
	Remove( Find( type ) );
}

Shader* ShaderManager::FindShader( const ShaderType type ) {
	Shader* shader = nullptr;
	ShaderNode* shadernode = Find( type );
	if ( shadernode ) {
		shader = shadernode->getData();
	}
	return shader;
}

void ShaderManager::LoadShaders() {
	printf( "  Loading shaders...\n" );
	AddShader( new Shader( ShaderType::Shader_Phong, "../ShaderManager/Phong" ) );
}

ShaderNode* ShaderManager::Find( const ShaderType type ) {
	ShaderNode* shader = nullptr;
	if ( type != ShaderType::Shader_None ) {
		ShaderNode* root = static_cast< ShaderNode* >(GetObjectList()->getRoot());

		if ( root ) {
			ShaderManager* instance = static_cast< ShaderManager* >(GetInstance());
			shader = instance->findDepthFirst( root, type );
		}
	}
	return shader;
}

ShaderNode* ShaderManager::findDepthFirst( ShaderNode* const walker, const ShaderType type ) {
	ShaderNode* shader = nullptr;

	if ( walker->getType() == type ) {
		shader = walker;
	} else {
		if ( walker->getChild() ) {
			shader = this->findDepthFirst( static_cast< ShaderNode* >(walker->getChild()), type );
		}
		if ( !shader && walker->getSibling() ) {
			shader = this->findDepthFirst( static_cast< ShaderNode* >(walker->getSibling()), type );
		}
	}
	return shader;
}