#include "ModelManager.h"
#include "Macros.h"

#include "ArchiveStructures.h"
#include "ModelNode.h"
#include "Model.h"
#include "Cube.h"
#include "GenericModel.h"
#include "Vertex.h"

#include <memory.h>

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
	printf("  Loading model from buffer...\n");
	ModelManager* instance = static_cast<ModelManager*>(GetInstance());
	void* ptr = buffer;

	GenericModel* model = new GenericModel(fileHeader.modelName);

	// Load vertices
	printf("    Loading vertices from buffer...\n");
	VerticesHeader* verticesHeader = reinterpret_cast<VerticesHeader*>(ptr);
	ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(verticesHeader));
	instance->loadVerticesFromBuffer(*model, *verticesHeader, ptr);

	// Load normals
	printf("   Loading normals from buffer...\n");
	ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) + verticesHeader->dataSize);
	NormalHeader* normalHeader = reinterpret_cast<NormalHeader*>(ptr);
	ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(normalHeader));
	instance->loadNormalsFromBuffer(*model, *normalHeader, ptr);

	// Load triangles
	printf("   Loading triangle list from buffer...\n");
	ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) + normalHeader->dataSize);
	TriangleHeader* triangleHeader = reinterpret_cast<TriangleHeader*>(ptr);
	ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) +sizeof(ptr) + sizeof(triangleHeader));
	instance->loadTrianglesFromBuffer(*model, *triangleHeader, ptr);

	model->updateVbos();
	AddModel(model);
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

void ModelManager::loadVerticesFromBuffer(Model& model, const VerticesHeader& header, void* const buffer) {
	printf("      Loading %i vertices...\n ", header.numVertices);
	Vector* buffVerts = reinterpret_cast<Vector*>(buffer);
	Vertex* verts = model.getVertices();

	if(!verts) {
		verts = new Vertex[header.numVertices];
	}
	for(int index = 0; index < header.numVertices; ++index) {
		verts[index].pos[X] = buffVerts[index].x;
		verts[index].pos[Y] = buffVerts[index].y;
		verts[index].pos[Z] = buffVerts[index].z;
		verts[index].pos[W] = 1.0f;
		verts[index].color = Vect(0.8f, 0.8f, 0.8f);
	}
	model.setVertices(verts);
	model.setNumVertices(header.numVertices);
}

void ModelManager::loadNormalsFromBuffer(Model& model, const NormalHeader& header, void* const buffer) {
	printf("      Loading %i normals...\n ", header.numNormals);
	Vector* buffNorms = reinterpret_cast<Vector*>(buffer);
	Vertex* norms = model.getVertices();

	if(!norms) {
		norms = new Vertex[header.numNormals];
	}
	for(int index = 0; index < header.numNormals; ++index) {
		norms[index].normal[X] = buffNorms[index].x;
		norms[index].normal[Y] = buffNorms[index].y;
		norms[index].normal[Z] = buffNorms[index].z;
		norms[index].normal[W] = 1.0f;
	}
	model.setVertices(norms);
	model.setNumVertices(header.numNormals);
}

void ModelManager::loadTrianglesFromBuffer(Model& model, const TriangleHeader& header, void* const buffer) {
	printf("      Loading %i triangles...\n ", header.numTriangles);
	Triangle* buffTris = reinterpret_cast<Triangle*>(buffer);
	int* faces = model.getFaces();

	if(!faces) {
		faces = new int[3 * header.numTriangles];
	}
	for(int index = 0; index < header.numTriangles; ++index) {
		faces[3 * index] = buffTris[index].a;
		faces[3 * index + 1] = buffTris[index].b;
		faces[3 * index + 2] = buffTris[index].c;
	}
	model.setFaces(faces);
	model.setNumFaces(header.numTriangles);
}