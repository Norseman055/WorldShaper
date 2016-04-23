#pragma once

#include "Manager.h"
#include "ModelTypes.h"

class ModelNode;
class Model;

class ModelManager : public Manager<Model*> {
public: 
	static void Startup();
	static void Shutdown();

	static void AddModel( Model* const );
	static void RemoveModel( const ModelType );

	static Model* FindModel( const ModelType );

private:
	static void LoadModels();
	static ModelNode* Find( const ModelType );

	ModelNode* findDepthFirst( ModelNode* const, const ModelType ) const;
};