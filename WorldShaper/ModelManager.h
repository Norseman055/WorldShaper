#pragma once

#include "Manager.h"
#include "ModelNode.h"

class ModelManager : public Manager<Model> {
public: 
	static void Startup();
	static void Shutdown();
	
	static Model* Find( ModelType );

private:
	Model* findDepthFirst( ModelNode* const, ModelType );
};