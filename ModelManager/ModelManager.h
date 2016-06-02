#pragma once

#include "Manager.h"
#include "ModelTypes.h"

class ModelNode;
class Model;
struct ModelFileHeader;
struct VerticesHeader;
struct NormalHeader;
struct TriangleHeader;

class ModelManager : public Manager<Model*> {
public:
	static void Startup();
	static void Shutdown();

	static void AddModel(Model* const);
	static void RemoveModel(const ModelType);

	static Model* FindModel(const ModelType);

	static void LoadModelFromBuffer(ModelFileHeader&, char* const);

private:
	static void LoadModels();
	static ModelNode* Find(const ModelType);

	ModelNode* findDepthFirst(ModelNode* const, const ModelType) const;

	void loadVerticesFromBuffer(Model&, const VerticesHeader&, void* const);
	void loadNormalsFromBuffer(Model&, const NormalHeader&, void* const);
	void loadTrianglesFromBuffer(Model&, const TriangleHeader&, void* const);
};