/// This converter class and almost every method in it is written by Vitor Fernandes. While some modifications may
/// have been made to a few of the functions, the majority of these functions are either direct copies or very close copies
/// of his work. All credit goes to him for this converter and the functionality therein. It has been modified for use
/// with my game engine, but is in no way work attributable to me.

#include "FbxConverter.h"
#include "Structures.h"

#include "fbxsdk.h"
#include <assert.h>

fbxsdk::FbxNode* const FindNode(const fbxsdk::FbxNodeAttribute::EType criteria, FbxNode* const root);
void ImportSkeletonRecursive(const fbxsdk::FbxNode * const node, const int parentIndex, const unsigned int level, vector<const Bone> & skeleton);
void ImportKeyframeRecursive(fbxsdk::FbxNode * const node, const FbxTime & time, Keyframe & keyframe);

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
	this->ImportAnimations();
	this->ImportSkin();
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

const vector<const Matrix>& FbxConverter::GetBindPose() const {
	return this->bindPose;
}

const vector<const Animation>& FbxConverter::GetAnimations() const {
	return this->animations;
}

const vector<vector<SkinInfluence>>& FbxConverter::GetSkin() const {
	return this->skin;
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

void FbxConverter::ImportSkin() {
	printf("Importing skeleton bind pose and skin...\n");
	using namespace fbxsdk;

	assert(this->fbxScene->GetRootNode());
	FbxNode* const node = FindNode(FbxNodeAttribute::eMesh, this->fbxScene->GetRootNode());
	assert(nullptr != node);
	FbxMesh* const mesh = static_cast<FbxMesh*>(node->GetNodeAttribute());
	assert(nullptr != mesh);

	const unsigned int skinCount = mesh->GetDeformerCount(FbxDeformer::eSkin);
	assert(1 == skinCount); // We will only handle one skin
	for (unsigned int skinIndex = 0; skinIndex < skinCount; skinIndex++)
	{
		const FbxSkin* const skin = static_cast<FbxSkin*>(mesh->GetDeformer(skinIndex, FbxDeformer::eSkin));
		const unsigned int clusterCount = skin->GetClusterCount();
		this->skin.resize(mesh->GetControlPointsCount());
		this->bindPose.resize(this->skeleton.size());
		for (unsigned int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++)
		{
			const FbxCluster* const cluster = skin->GetCluster(clusterIndex);

			bool foundBone = false;
			unsigned int boneIndex;
			for (boneIndex = 0; boneIndex < this->skeleton.size(); boneIndex++)
			{
				if (nullptr != cluster->GetLink() && strcmp(cluster->GetLink()->GetName(), this->skeleton[boneIndex].boneName) == 0)
				{
					foundBone = true;
					break;
				}
			}
			if (foundBone)
			{
				// Usually Identity, but the SDK states that it should also be used
				const FbxNode* const node = cluster->GetLink();
				const FbxVector4 geometricTranslation = node->GetGeometricTranslation(FbxNode::eSourcePivot);
				const FbxVector4 geometricRotation = node->GetGeometricRotation(FbxNode::eSourcePivot);
				const FbxVector4 geometricScaling = node->GetGeometricScaling(FbxNode::eSourcePivot);
				const FbxAMatrix geometryMatrix(geometricTranslation, geometricRotation, geometricScaling);

				// Node Transform
				FbxAMatrix nodeTransform;
				cluster->GetTransformMatrix(nodeTransform);

				// Link Transform - This should be the bind pose
				FbxAMatrix linkTransform;
				cluster->GetTransformLinkMatrix(linkTransform);

				FbxAMatrix bindPoseMatrix = linkTransform.Inverse() * nodeTransform * geometryMatrix;
				for (int row = 0; row < 4; row++)
				{
					for (int col = 0; col < 4; col++)
					{
						this->bindPose[boneIndex].elements[row][col] = static_cast<float>(bindPoseMatrix[row][col]);
					}
				}
				const unsigned int vertexCount = cluster->GetControlPointIndicesCount();
				const int * const vertexIndices = cluster->GetControlPointIndices();
				const double* const vertexWeights = cluster->GetControlPointWeights();
				for (unsigned int i = 0; i < vertexCount; i++)
				{
					SkinInfluence influence;
					influence.boneIndex = boneIndex;
					influence.weight = static_cast<float>(vertexWeights[i]);
					this->skin[vertexIndices[i]].push_back(influence);
				}
			}
		}
	}
}

void FbxConverter::ImportAnimations() {
	printf("Importing animation keyframes...\n");
	using namespace fbxsdk;

	const int animStackCount = this->fbxScene->GetSrcObjectCount<FbxAnimStack>();
	this->animations.reserve(animStackCount);
	for(int index = 0; index < animStackCount; index++) {
		FbxAnimStack* const animStack = this->fbxScene->GetSrcObject<FbxAnimStack>(index);
		this->fbxScene->SetCurrentAnimationStack(animStack);
		const FbxTime start = animStack->GetLocalTimeSpan().GetStart();
		const FbxTime stop = animStack->GetLocalTimeSpan().GetStop();

		Animation animation;
		int animNameLen = strlen(animStack->GetName());
		if(animNameLen < 16) {
			memcpy(animation.animName, animStack->GetName(), animNameLen);
			animation.animName[animNameLen] = '\0';
		} else {
			memcpy(animation.animName, animStack->GetName(), 15);
			animation.animName[15] = '\0';
		}

		animation.numKeyframes = static_cast<unsigned int>(stop.GetFrameCount()) + 1;
		animation.keyframes.reserve(animation.numKeyframes);
		FbxTime time;
		for(unsigned int frame = 0; frame < animation.numKeyframes; frame++) {
			time.SetTime(0, 0, 0, frame, 0, 0, FbxTime::GetGlobalTimeMode());
			FbxNode* const skeletonRoot = FindNode(FbxNodeAttribute::eSkeleton, this->fbxScene->GetRootNode());
			assert(skeletonRoot);
			Keyframe keyframe;
			keyframe.time = time.GetMilliSeconds() * 0.001f;
			ImportKeyframeRecursive(skeletonRoot, time, keyframe);
			keyframe.numTransforms = keyframe.boneTransforms.size();
			animation.keyframes.push_back(keyframe);
		}
		this->animations.push_back(animation);
	}
}

void ImportKeyframeRecursive(fbxsdk::FbxNode * const root, const FbxTime & time, Keyframe & keyframe) {
	assert(root);
	assert(&time);
	assert(&keyframe);

	const FbxAMatrix matrix = root->EvaluateLocalTransform(time);
	const FbxVector4 translation = matrix.GetT();
	const FbxQuaternion rotation = matrix.GetQ();
	const FbxVector4 scale = matrix.GetS();
	TransformData transform;
	transform.translation.x = static_cast<float>(translation[0]);
	transform.translation.y = static_cast<float>(translation[1]);
	transform.translation.z = static_cast<float>(translation[2]);
	transform.rotation.x = static_cast<float>(rotation[0]);
	transform.rotation.y = static_cast<float>(rotation[1]);
	transform.rotation.z = static_cast<float>(rotation[2]);
	transform.rotation.w = static_cast<float>(rotation[3]);
	transform.scale.x = static_cast<float>(scale[0]);
	transform.scale.y = static_cast<float>(scale[1]);
	transform.scale.z = static_cast<float>(scale[2]);

	keyframe.boneTransforms.push_back(transform);
	for(int i = 0; i < root->GetChildCount(); i++) {
		ImportKeyframeRecursive(root->GetChild(i), time, keyframe);
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