#include "ModelManager.h"

#include "Macros.h"
#include "ArchiveStructures.h"
#include "ModelNode.h"
#include "Model.h"
#include "Cube.h"
#include "GenericModel.h"

void ModelManager::Startup() {
	printf("\n===== Starting Model Manager =====\n");
	GetInstance();
	LoadModels();
	printf("===== Model Manager started =====\n\n");
}

void ModelManager::Shutdown() {
	Cleanup();
	DestroyInstance();
}

void ModelManager::AddModel(Model* const model) {
	// Only add model to manager if unique model. No need for duplicates.
	if(!Find(model->getType())) {
		Add(new ModelNode(model));
	}
}

void ModelManager::RemoveModel(const ModelType type) {
	Remove(Find(type));
}

Model* ModelManager::FindModel(const ModelType type) {
	Model* model = nullptr;
	ModelNode* modelnode = Find(type);
	if(modelnode) {
		model = modelnode->getData();
	}
	return model;
}

void ModelManager::LoadModelFromBuffer(ModelFileHeader& fileHeader, char* const buffer) {
	printf("  Loading model from buffer... \n");
	ModelManager* instance = static_cast<ModelManager*>(GetInstance());
	void* ptr = buffer;

	GenericModel model(fileHeader.modelName);

	// Load vertices
	printf("    Loading vertices from buffer...\n");
	VerticesHeader* verticesHeader = reinterpret_cast<VerticesHeader*>(ptr);
	char* vertBuffer = new char[verticesHeader->dataSize];
	instance->loadVerticesFromBuffer(model, *verticesHeader, vertBuffer);

	// Load normals
	printf("    Loading normals from buffer...\n");
	ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(verticesHeader) + verticesHeader->dataSize);
	NormalHeader* normalHeader = reinterpret_cast<NormalHeader*>(ptr);
	char* normalBuffer = new char[normalHeader->dataSize];
	instance->loadNormalsFromBuffer(model, *normalHeader, normalBuffer);

	// Load triangles
	printf("    Loading triangle list from buffer...\n");
	ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(normalHeader) + normalHeader->dataSize);
	TriangleHeader* triangleHeader = reinterpret_cast<TriangleHeader*>(ptr);
	char* triangleBuffer = new char[triangleHeader->dataSize];
	instance->loadTrianglesFromBuffer(model, *triangleHeader, triangleBuffer);

	delete vertBuffer;
	delete normalBuffer;
	delete triangleBuffer;
}

void ModelManager::LoadModels() {
	printf("  Loading models...\n");
	AddModel(new Cube);
}

ModelNode* ModelManager::Find(const ModelType type) {
	ModelNode* model = nullptr;
	if(type != ModelType::Model_None) {
		ModelNode* root = static_cast<ModelNode*>(GetObjectList()->getRoot());

		if(root) {
			ModelManager* instance = static_cast<ModelManager*>(GetInstance());
			model = instance->findDepthFirst(root, type);
		}
	}
	return model;
}

ModelNode* ModelManager::findDepthFirst(ModelNode* const walker, const ModelType type) const {
	ModelNode* model = nullptr;

	if(walker->getType() == type) {
		model = walker;
	} else {
		if(walker->getChild()) {
			model = this->findDepthFirst(static_cast<ModelNode*>(walker->getChild()), type);
		}
		if(!model && walker->getSibling()) {
			model = this->findDepthFirst(static_cast<ModelNode*>(walker->getSibling()), type);
		}
	}
	return model;
}

void ModelManager::loadVerticesFromBuffer(Model& model, const VerticesHeader& header, const char* buffer) {
	UNUSED(model);
	UNUSED(buffer);
	printf("    Loading %i vertices... ", header.numVertices);
	printf(" Success!\n");
}

void ModelManager::loadNormalsFromBuffer(Model& model, const NormalHeader& header, const char* buffer) {
	UNUSED(model);
	UNUSED(buffer);
	printf("    Loading %i normals... ", header.numNormals);
	printf(" Success!\n");
}

void ModelManager::loadTrianglesFromBuffer(Model& model, const TriangleHeader& header, const char* buffer) {
	UNUSED(model);
	UNUSED(buffer);
	printf("    Loading %i triangles... ", header.numTriangles);
	printf(" Success!\n");
}