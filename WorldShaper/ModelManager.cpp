#include "ModelManager.h"

void ModelManager::Startup() {
	GetInstance();
}

void ModelManager::Shutdown() {
	Cleanup();
	DestroyInstance();
}

Model* ModelManager::Find( ModelType type ) {
	Model* model = nullptr;
	if ( type != Model_None ) {
		ModelNode* root = static_cast< ModelNode* >(GetObjectList()->getRoot());

		if ( root->getChild() ) {
			ModelManager* instance = static_cast< ModelManager* >(GetInstance());
			model = instance->findDepthFirst( static_cast< ModelNode* >(root->getChild()), type );
		}
	}
	
	return model;
}

Model* ModelManager::findDepthFirst( ModelNode* const walker, ModelType type ) {
	Model* model = nullptr;

	if ( walker->getType() == type ) {
		model = walker->getData();
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