#include "ModelManager.h"

#include "ModelNode.h"
#include "Model.h"
#include "Cube.h"

void ModelManager::Startup() {
	printf( "\n===== Starting Model Manager =====\n" );
	GetInstance();
	LoadModels();
	printf( "===== Model Manager started =====\n\n" );
}

void ModelManager::Shutdown() {
	Cleanup();
	DestroyInstance();
}

void ModelManager::AddModel( Model* const model ) {
	// Only add model to manager if unique model. No need for duplicates.
	if ( !Find( model->getType() ) ) {
		Add( new ModelNode( model ) );
	}
}

void ModelManager::RemoveModel( const ModelType type ) {
	Remove( Find( type ) );
}

Model* ModelManager::FindModel( const ModelType type ) {
	Model* model = nullptr;
	ModelNode* modelnode = Find( type );
	if ( modelnode ) {
		model = modelnode->getData();
	}
	return model;
}

void ModelManager::LoadModels() {
	printf( "  Loading models...\n" );
	AddModel( new Cube );
}

ModelNode* ModelManager::Find( ModelType type ) {
	ModelNode* model = nullptr;
	if ( type != Model_None ) {
		ModelNode* root = static_cast< ModelNode* >(GetObjectList()->getRoot());

		if ( root ) {
			ModelManager* instance = static_cast< ModelManager* >(GetInstance());
			model = instance->findDepthFirst( root, type );
		}
	}
	
	return model;
}

ModelNode* ModelManager::findDepthFirst( ModelNode* const walker, const ModelType type ) {
	ModelNode* model = nullptr;

	if ( walker->getType() == type ) {
		model = walker;
	} else {
		if ( walker->getChild() ) {
			model = this->findDepthFirst( static_cast< ModelNode* >(walker->getChild()), type );
		}
		if ( model == nullptr && walker->getSibling() ) {
			model = this->findDepthFirst( static_cast< ModelNode* >(walker->getSibling()), type );
		}
	}
	
	return model;
}