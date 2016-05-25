/// This converter class and almost every method in it is written by Vitor Fernandes. While some modifications may
/// have been made to a few of the functions, the majority of these functions are either direct copies or very close copies
/// of his work. All credit goes to him for this converter and the functionality therein. It has been modified for use
/// with my game engine, but is in no way work attributable to me.

#include "FbxConverter.h"
#include "Structures.h"

#include <fbxsdk.h>
#include <assert.h>

fbxsdk::FbxNode* const FindNode(const fbxsdk::FbxNodeAttribute::EType criteria, FbxNode* const root);
void ImportSkeletonRecursive(const fbxsdk::FbxNode * const node, const int parentIndex, const unsigned int level, vector<const Bone> & skeleton);

void FbxConverter::Import(const char* filename) {

	this->vertices.clear();
	this->normals.clear();
	this->triangles.clear();

	using namespace fbxsdk;

	printf("Opening file: %s \n", filename);
	FbxImporter* const importer = FbxImporter::Create(this->fbxManager, "Fbx Importer");
	const FbxString file = (filename);
	const bool error = importer->Initialize(file);
	assert(error);

	int major, minor, revision;
	importer->GetFileVersion(major, minor, revision);
	printf("FBX file format version for file: %i.%i.%i \n", major, minor, revision);

	importer->Import(this->fbxScene);
	importer->Destroy();

	FbxGeometryConverter geoConverter(this->fbxManager);
	geoConverter.Triangulate(this->fbxScene, true);
	geoConverter.SplitMeshesPerMaterial(this->fbxScene, true);

	this->ImportVertices();
	this->ImportNormals();
	this->ImportTriangles();
	this->ImportSkeleton();
}

const vector<const Vector>& FbxConverter::GetVertices() const {
	return this->vertices;
}

const vector<const Vector>& FbxConverter::GetNormals() const {
	return this->normals;
}

const vector<const Triangle>& FbxConverter::GetTriangles() const {
	return this->triangles;
}

const vector<const Bone>& FbxConverter::GetSkeleton() const {
	return this->skeleton;
}

void FbxConverter::ImportVertices() {
	printf("Importing vertices...\n");
	using namespace fbxsdk;
	
	assert(this->fbxScene->GetRootNode());
	
	FbxNode* const node = FindNode(FbxNodeAttribute::eMesh, this->fbxScene->GetRootNode());
	assert(node);
	FbxMesh* const mesh = static_cast<FbxMesh*>(node->GetNodeAttribute());
	assert(mesh);
	mesh->SplitPoints();
	assert(!mesh->CheckSamePointTwice());

	const int vertexCount = mesh->GetControlPointsCount();
	const FbxVector4* const vertices = mesh->GetControlPoints();

	assert(vertexCount > 0);
	assert(vertices);

	this->vertices.reserve(vertexCount);
	for(int index = 0; index < vertexCount; index++) {
		Vector position;
		position.x = static_cast<float>(vertices[index][0]);
		position.y = static_cast<float>(vertices[index][1]);
		position.z = static_cast<float>(vertices[index][2]);
		this->vertices.push_back(position);
	}
}

void FbxConverter::ImportNormals() {
	printf("Importing normals...\n");
	using namespace fbxsdk;

	FbxNode* const node = FindNode(FbxNodeAttribute::eMesh, this->fbxScene->GetRootNode());
	assert(node);
	FbxMesh* const mesh = static_cast<FbxMesh*>(node->GetNodeAttribute());
	assert(mesh);
	mesh->GenerateNormals(false, true);
	assert(mesh->CheckIfVertexNormalsCCW());

	const int vertexCount = mesh->GetControlPointsCount();
	const int normalCount = mesh->GetElementNormalCount();
	const FbxGeometryElementNormal* const normals = mesh->GetElementNormal();

	assert(normalCount > 0);
	assert(normals);
	assert(FbxGeometryElement::eByControlPoint == normals->GetMappingMode());
	assert(FbxGeometryElement::eDirect == normals->GetReferenceMode());

	this->normals.reserve(vertexCount);
	for(int index = 0; index < vertexCount; index++) {
		Vector normal;
		normal.x = static_cast<float>(normals->GetDirectArray()[index][0]);
		normal.y = static_cast<float>(normals->GetDirectArray()[index][1]);
		normal.z = static_cast<float>(normals->GetDirectArray()[index][2]);
		this->normals.push_back(normal);
	}
}

void FbxConverter::ImportTriangles() {
	printf("Importing triangles...\n");
	using namespace fbxsdk;

	FbxNode* const node = FindNode(FbxNodeAttribute::eMesh, this->fbxScene->GetRootNode());
	assert(node);
	FbxMesh* const mesh = static_cast<FbxMesh*>(node->GetNodeAttribute());
	assert(mesh);

	const int polygonCount = mesh->GetPolygonCount();
	const int* const polygons = mesh->GetPolygonVertices();

	assert(polygonCount > 0);
	assert(polygons);

	this->triangles.reserve(polygonCount);
	for(int index = 0; index < polygonCount; index++) {
		Triangle triangle;
		triangle.c = static_cast<unsigned int>(polygons[3 * index]);
		triangle.b = static_cast<unsigned int>(polygons[3 * index + 1]);
		triangle.a = static_cast<unsigned int>(polygons[3 * index + 2]);
		this->triangles.push_back(triangle);
	}
}

void FbxConverter::ImportSkeleton() {
	printf("Importing skeleton hierarchy...\n");
	using namespace fbxsdk;

	const FbxNode* skeletonRoot = FindNode(FbxNodeAttribute::eSkeleton, this->fbxScene->GetRootNode());
	assert(skeletonRoot);

	ImportSkeletonRecursive(skeletonRoot, -1, 0, this->skeleton);
}

void ImportSkeletonRecursive(const fbxsdk::FbxNode* const node, const int parentIndex, const unsigned int level, vector<const Bone>& skeleton) {
	assert(node);
	assert(&skeleton);

	const char* boneName = node->GetName();

	Bone bone;
	int boneNameLen = strlen(boneName);
	if(boneNameLen < 32) {
		memcpy(bone.boneName, boneName, boneNameLen);
		bone.boneName[boneNameLen] = '\0';
	} else {
		memcpy(bone.boneName, boneName, 31);
		bone.boneName[31] = '\0';
	}

	bone.parentIndex = parentIndex;
	bone.level = level;
	const int myIndex = skeleton.size();
	skeleton.push_back(bone);

	for(int i = 0; i < node->GetChildCount(); i++) {
		ImportSkeletonRecursive(node->GetChild(i), myIndex, level + 1, skeleton);
	}
}

FbxConverter::FbxConverter() 
	: fbxManager(fbxsdk::FbxManager::Create()), fbxScene(fbxsdk::FbxScene::Create(this->fbxManager, "Fbx Scene"))
{
	assert(this->fbxManager);
	assert(this->fbxScene);
	
	printf("FBX SDK Version: %s \n", this->fbxManager->GetVersion());

	int major, minor, revision;
	this->fbxManager->GetFileFormatVersion(major, minor, revision);
	printf("FBX file format version: %i.%i.%i \n", major, minor, revision);
}

FbxConverter::~FbxConverter() { 
	this->fbxScene->Destroy();
	this->fbxManager->Destroy();
}

fbxsdk::FbxNode* const FindNode(const fbxsdk::FbxNodeAttribute::EType criteria, FbxNode* const root) {
	using namespace fbxsdk;

	assert(nullptr != root);

	FbxNode * result = nullptr;
	const FbxNodeAttribute* const attribute = root->GetNodeAttribute();
	if(NULL != attribute && criteria == attribute->GetAttributeType()) {
		result = root;
	} else {
		for(int i = 0; i < root->GetChildCount() && nullptr == result; i++) {
			result = FindNode(criteria, root->GetChild(i));
		}
	}

	return result;
}