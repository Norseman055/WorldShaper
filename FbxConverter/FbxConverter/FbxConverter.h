/// This converter class and almost every method in it is written by Vitor Fernandes. While some modifications may
/// have been made to a few of the functions, the majority of these functions are either direct copies or very close copies
/// of his work. All credit goes to him for this converter and the functionality therein. It has been modified for use
/// with my game engine, but is in no way work attributable to me.

#ifndef FBX_CONVERTER_H
#define FBX_CONVERTER_H

#include <vector>

using namespace std;

namespace fbxsdk {
	class FbxManager;
	class FbxScene;
}

struct Vector;
struct Triangle;
struct Bone;

class FbxConverter {
public:
	void Import(const char* filepath);
	const vector<const Vector>& GetVertices() const;
	const vector<const Vector>& GetNormals() const;
	const vector<const Triangle>& GetTriangles() const;
	const vector<const Bone>& GetSkeleton() const;

	FbxConverter();
	~FbxConverter();

	// No copy or assignment
	FbxConverter(FbxConverter&) = delete;
	FbxConverter& operator=(FbxConverter&) = delete;

private:
	void ImportVertices();
	void ImportNormals();
	void ImportTriangles();
	void ImportSkeleton();

private:
	vector<const Vector> vertices;
	vector<const Vector> normals;
	vector<const Triangle> triangles;
	vector<const Bone> skeleton;

	fbxsdk::FbxManager* const fbxManager;
	fbxsdk::FbxScene* const fbxScene;
};

#endif